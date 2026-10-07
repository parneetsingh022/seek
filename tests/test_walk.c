#ifdef __linux__
#define _XOPEN_SOURCE 700
#elif defined(__APPLE__)
#define _DARWIN_C_SOURCE
#endif

#include "unity.h"

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#include <seek/walk.h>

static char temp_dir[256];
static char paths[16][PATH_MAX];
static int path_count;

static int remove_entry(const char *path,
             const struct stat *info,
             int type,
             struct FTW *ftwbuf)
{
    (void)info;
    (void)type;
    (void)ftwbuf;

    return remove(path);
}

void setUp(void)
{
    path_count = 0;

    strcpy(temp_dir, "/tmp/seek-test-XXXXXX");

    char *result = mkdtemp(temp_dir);
    TEST_ASSERT_NOT_NULL(result);
}


void tearDown(void)
{
    TEST_ASSERT_EQUAL(0,
                      nftw(temp_dir,
                           remove_entry,
                           10,
                           FTW_DEPTH | FTW_PHYS));
}

/*
 * Callback used by the tests.
 */
static void record_path(const char *path, struct stat *info)
{
    TEST_ASSERT_NOT_NULL(path);
    TEST_ASSERT_NOT_NULL(info);

    TEST_ASSERT_LESS_THAN(16, path_count);

    strcpy(paths[path_count], path);
    path_count++;
}

/*
 * Creates a regular file.
 */
static void create_file(const char *path)
{
    FILE *file = fopen(path, "w");

    TEST_ASSERT_NOT_NULL(file);

    fclose(file);
}

/*
 * Test that walk_dir() finds a regular file.
 */
void test_walk_dir_finds_file(void)
{
    char file_path[PATH_MAX];

    snprintf(file_path, sizeof(file_path),
             "%s/test.txt", temp_dir);

    create_file(file_path);

    walk_dir(temp_dir, record_path, false);

    TEST_ASSERT_EQUAL(1, path_count);
    TEST_ASSERT_EQUAL_STRING(file_path, paths[0]);
}

/*
 * Test that walk_dir() finds a directory.
 */
void test_walk_dir_finds_directory(void)
{
    char dir_path[PATH_MAX];

    snprintf(dir_path, sizeof(dir_path),
             "%s/subdir", temp_dir);

    int result = mkdir(dir_path, 0700);

    TEST_ASSERT_EQUAL(0, result);

    walk_dir(temp_dir, record_path, false);

    TEST_ASSERT_EQUAL(1, path_count);
    TEST_ASSERT_EQUAL_STRING(dir_path, paths[0]);
}

/*
 * Test that walk_dir() finds multiple entries.
 */
void test_walk_dir_finds_multiple_entries(void)
{
    char file_path[PATH_MAX];
    char dir_path[PATH_MAX];

    snprintf(file_path, sizeof(file_path),
             "%s/test.txt", temp_dir);

    snprintf(dir_path, sizeof(dir_path),
             "%s/subdir", temp_dir);

    create_file(file_path);

    int result = mkdir(dir_path, 0700);
    TEST_ASSERT_EQUAL(0, result);

    walk_dir(temp_dir, record_path, false);

    TEST_ASSERT_EQUAL(2, path_count);

    /*
     * readdir() does not guarantee ordering, so don't assume
     * paths[0] is the file and paths[1] is the directory.
     */
    bool found_file = false;
    bool found_dir = false;

    for (int i = 0; i < path_count; i++) {
        if (strcmp(paths[i], file_path) == 0)
            found_file = true;

        if (strcmp(paths[i], dir_path) == 0)
            found_dir = true;
    }

    TEST_ASSERT_TRUE(found_file);
    TEST_ASSERT_TRUE(found_dir);
}

/*
 * Test that "." and ".." are not passed to the callback.
 */
void test_walk_dir_skips_special_entries(void)
{
    walk_dir(temp_dir, record_path, false);

    TEST_ASSERT_EQUAL(0, path_count);
}

/**
 * Verifies that walk_dir() only visits entries in the specified
 * directory when recursive traversal is disabled.
 */
void test_walk_dir_non_recursive(void)
{
    char subdir[PATH_MAX];
    char nested_file[PATH_MAX];

    snprintf(subdir, sizeof(subdir),
             "%s/subdir", temp_dir);

    snprintf(nested_file, sizeof(nested_file),
             "%s/subdir/nested.txt", temp_dir);

    TEST_ASSERT_EQUAL(0, mkdir(subdir, 0700));

    create_file(nested_file);

    walk_dir(temp_dir, record_path, false);

    /*
     * Only the immediate subdirectory should be visited.
     */
    TEST_ASSERT_EQUAL(1, path_count);
    TEST_ASSERT_EQUAL_STRING(subdir, paths[0]);
}

/**
 * Verifies that walk_dir() recursively visits entries in
 * nested subdirectories when recursive traversal is enabled.
 */
void test_walk_dir_recursive(void)
{
    char level1[PATH_MAX];
    char level2[PATH_MAX];
    char level3[PATH_MAX];
    char file1[PATH_MAX];
    char file2[PATH_MAX];
    char file3[PATH_MAX];

    snprintf(level1, sizeof(level1),
             "%s/level1", temp_dir);

    snprintf(level2, sizeof(level2),
             "%s/level1/level2", temp_dir);

    snprintf(level3, sizeof(level3),
             "%s/level1/level2/level3", temp_dir);

    snprintf(file1, sizeof(file1),
             "%s/level1/file1.txt", temp_dir);

    snprintf(file2, sizeof(file2),
             "%s/level1/level2/file2.txt", temp_dir);

    snprintf(file3, sizeof(file3),
             "%s/level1/level2/level3/file3.txt", temp_dir);

    TEST_ASSERT_EQUAL(0, mkdir(level1, 0700));
    TEST_ASSERT_EQUAL(0, mkdir(level2, 0700));
    TEST_ASSERT_EQUAL(0, mkdir(level3, 0700));

    create_file(file1);
    create_file(file2);
    create_file(file3);

    walk_dir(temp_dir, record_path, true);

    /*
     * We should see every directory and file at all three levels.
     */
    TEST_ASSERT_EQUAL(6, path_count);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_walk_dir_finds_file);
    RUN_TEST(test_walk_dir_finds_directory);
    RUN_TEST(test_walk_dir_finds_multiple_entries);
    RUN_TEST(test_walk_dir_skips_special_entries);
    RUN_TEST(test_walk_dir_non_recursive);
    RUN_TEST(test_walk_dir_recursive);

    return UNITY_END();
}

# seek

A lightweight command-line tool for searching text in files, written in C.

`seek` recursively searches directories for files containing a specified string and prints matching lines.

## Installation

### Homebrew

Install `seek` on macOS or Linux using Homebrew:

```bash
brew install parneetsingh022/tap/seek
```

To update to the latest available version:

```bash
brew update
brew upgrade parneetsingh022/tap/seek
```

### Build from source

Clone the repository:

```bash
git clone https://github.com/parneetsingh022/seek.git
cd seek
```

Build the project:

```bash
make
```

Run the executable:

```bash
./build/seek "hello"
```

## Usage

```bash
seek <pattern>
```

Search for a string in the current directory:

```bash
seek hello
```

Search for a function declaration:

```bash
seek "int main"
```


By default, `seek` searches the current directory and its subdirectories.


## Development

Build the project:

```bash
make
```

Run the test suite:

```bash
make test
```

The project uses [Unity](https://github.com/ThrowTheSwitch/Unity) for unit testing.


## Contributing & Formatting

We use `clang-format` (v22) to enforce code style. Please run `make format` before opening a pull request. 

For full setup instructions and CI details, see [CONTRIBUTING.md](CONTRIBUTING.md).

## Platform Support

`seek` currently supports:

- Linux (x86-64)
- macOS (Intel and Apple Silicon)

Windows is not currently supported.

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for release history and upcoming changes.

## License

See the [LICENSE](LICENSE) file for licensing information.
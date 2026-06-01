# Firstwords

**Firstwords** is a playful, terminal-based AI baby that learns language from you.

You type sentences. It remembers trigrams. Over time, it builds a vocabulary and starts talking back — starting with babble, gradually shifting to real words it's seen before. Every conversation is stored locally, so the baby's personality grows with yours.

It's part toy, part Markov-chain experiment, and entirely meant to be run in a terminal window for a few minutes of strange joy.

## How it works

1. You type something.
2. Firstwords breaks it into trigrams (groups of 3 consecutive words) and stores them in a SQLite database.
3. The more unique words you teach it, the higher its *maturity* climbs (from 0% to 100%).
4. When responding, it looks at the last two words you said and tries to find a matching trigram. If its maturity is high enough, it uses a real word you've taught it. Otherwise — or if no match is found — it babbles a random made-up syllable.

So the baby literally learns to echo patterns from you, and the more you talk, the more "grown up" its responses become.

## Prerequisites

- A C++17 compiler (Clang or GCC)
- [CMake](https://cmake.org/) 3.14 or higher
- [SQLite](https://sqlite.org/) 3 (system-installed or via package manager)

All other dependencies are vendored:
- [nlohmann/json](https://github.com/nlohmann/json) — bundled as `thirdparty/json.hpp`
- [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp) — bundled at `thirdparty/SQLiteCpp-3.3.3`

## Build

```bash
git clone https://github.com/yourusername/firstwords.git
cd firstwords
mkdir build && cd build
cmake ..
make
```

This produces a `main` executable in the `build/` directory.

## Usage

Run the executable:

```bash
./main
```

The database and vocabulary data are stored in:

```
~/Library/Application Support/Firstwords/
```

> **Note:** This path is currently hardcoded for macOS. The project builds cross-platform thanks to CMake, but the data directory will need adjustment to run on Linux or Windows. Contributions to make this portable are very welcome — see [CONTRIBUTING.md](CONTRIBUTING.md).

Once running, you'll see:

```
System: Baby is awake and listening... (type /night to leave)

You:
```

Type anything. The baby learns and responds. Type `/night` to quit.

```
You: hello little one
bababoo
You: how are you today?
meefla
You: I think you're learning
...
```

## Contributing

This project welcomes contributions — whether it's porting the data path to other platforms, adding a persistent baby name, or making the responses weirder.

Check out [CONTRIBUTING.md](CONTRIBUTING.md) for setup instructions, coding conventions, and how to submit changes.

## Acknowledgments

- `utils.hpp` functions generated with [DeepSeek AI](https://deepseek.com)
- `AutoSaveStorage.hpp` generated with [Google Gemini](https://gemini.google.com)
- Built with [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp) and [nlohmann/json](https://github.com/nlohmann/json)
# Ethio-Gregorean Calendar

A C++ program that displays the calendar in both Gregorian and Ethiopian formats simultaneously.

**Note:** Holidays are only displayed starting from 1900, as some holidays do not make sense before that year.

---

## Usage

```
ecal [<month: 1-12> (optional)] [<year: 1-4599> (optional)]
```

Inputs are received in Gregorian month and Gregorian year.

---

## Compilation Guide

### Windows

Compile using either:

```sh
clang @sources.txt -o ecal.exe
```

or

```sh
g++ @sources.txt -o ecal.exe
```

> `@sources.txt` contains the list of source files. Run this command in the directory where you cloned the repo.

To use `ecal` from the terminal anywhere:

1. Copy `ecal.exe` to `C:/ProgramFiles/ecal/`
2. Add `C:/ProgramFiles/ecal` to your system's environment variables.

---

### Linux

Run the install script:

```sh
curl -f https://raw.githubusercontent.com/Enoch-Tadesse/Calendar/main/install.sh | bash
```

You will be prompted for your user password.

Then run:

```sh
ecal
```

---

### Arch Linux or Manual Installation

Compile with:

```sh
clang @sources.txt -o ecal.exe
```

or

```sh
g++ @sources.txt -o ecal.exe
```

Then copy the executable to a system path:

```sh
sudo cp ./ecal.exe /usr/bin/ecal
```

---

## Contact

- Telegram: [@the_CS_guy](https://t.me/the_CS_guy)  
- Email: henitadesse97@gmail.com  
- GitHub: [https://github.com/Enoch-Tadesse](https://github.com/Enoch-Tadesse)

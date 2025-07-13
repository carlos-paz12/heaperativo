# heaperativo
Implementation of a process manager using a heap structure.

## Introduction

**heaperativo** is a simple process manager simulator built in C using a **Min-Heap** as the core data structure.

This project aims to solidify understanding of heaps by simulating process scheduling. The heap stores `Process` elements, prioritizing them based on a calculated key (`time_to_kill - time_used`), ensuring that processes with lower remaining time are executed first.

The simulator performs:
- Heap-based priority scheduling
- Process execution simulation (`execute_Process`)
- Key updates for all processes
- Conditional root removal (only if key == 0)
- Queue <-> Heap conversions

It was developed as part of the _Estrutura de Dados Básicas II_ course at **UFRN**.

## How It Works

The simulator runs in a loop until the heap is empty:

1. A random number `n` (≤ heap size) is generated.
2. The first `n` processes in the heap are executed (`execute_Process`).
3. After execution, all heap keys are updated.
4. The root of the heap is removed only if its key is 0.
5. The heap reorders automatically after each operation.

## Compiling and Running
> [!note]
> This method requires CMake (>= 3.22.1) to be installed on your system. CMake is a cross-platform build system generator used to configure and compile the project. If it's not already installed, you can install it using your system’s package manager (e.g., `sudo apt install cmake` on Debian/Ubuntu or `brew install cmake` on macOS).

Once CMake is set up, follow the steps:

1. Clone this repository:

```bash
git clone https://github.com/carlos-paz12/heaperativo
```

2. Navigate to the project directory:

```bash
cd heaperativo
```

3. Compile and build the program using `cmake`:

```bash
cmake -S . -B build
cmake --build build
```

4. Run:

```bash
./bin/heaperativo
```

## Authors
<table align="center">
  <tr>
    <td align="center">
      <a href="https://github.com/carolln">
        <img src="https://github.com/carolln.png" width="60" style="border-radius: 50%; margin: 5px;" />
      </a>
      <br />
      <sub><b>Carolina Nunes</b></sub>
    </td>
    <td align="center">
  <a href="https://github.com/luanZd">
    <img src="https://github.com/luanZd.png" width="60" style="border-radius: 50%; margin: 5px;" />
  </a>
      <br />
      <sub><b>Diego Luan</b></sub>
    </td>
    <td align="center">
  <a href="https://github.com/flavinhojrz">
    <img src="https://github.com/flavinhojrz.png" width="60" style="border-radius: 50%; margin: 5px;" />
  </a>
      <br />
      <sub><b>Flávio Júnior</b></sub>
    </td>
    <td align="center">
  <a href="https://github.com/carlos-paz12">
    <img src="https://github.com/carlos-paz12.png" width="60" style="border-radius: 50%; margin: 5px;" />
  </a>
      <br />
      <sub><b>Carlos Paz</b></sub>
    </td>
    <td align="center">
  <a href="https://github.com/leandroaa01">
    <img src="https://github.com/leandroaa01.png" width="60" style="border-radius: 50%; margin: 5px;" />
  </a>
      <br />
      <sub><b>Leandro Andrade</b></sub>
    </td>
    <td align="center">
  <a href="https://github.com/lirubiru">
    <img src="https://github.com/lirubiru.png" width="60" style="border-radius: 50%; margin: 5px;" />
  </a>
      <br />
      <sub><b>Lucas Graziano</b></sub>
    </td>
  </tr>
</table>

---

<div align="center"> &copy; DIMAp | Departamento de Informática e Matemática Aplicada - 2025 </div>

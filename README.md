*This project has been created as part of the 42 curriculum by naportel.*

# Description

Codexion is program written in C that simulates a circle table of coders which each coder have to compile a Quantum Code.
To compile, each coder needs two USB dongles, and there are just as much dongles as coders, so they have to temporarily borrow a USB dongle from the next coder to do their routine.
Eventually, some coder will have to await the next/previous coder to release their dongle, however, if one wait more than a certain time they'll have a **burnout**!
Luckily, there's a *monitor* to keep all coders have in an policy when multiple coders wants the same dongle, the policies can be either "fifo" (first in, first out) or "edf" (Earliest Deadline First).
The program only ends once all of the coders have done all their compiles or when one have a "burnout" for not getting a dongle after a certain time.

## Blocking cases handled

### Resource Contetion

### Deadlock Prevention

### Starvation

### Burnout

### Dongle Cooldown

## Thread synchronization mechanisms

### Mutex

### Condition Variables

### Scheduling Policies (FIFO / EDF)

# Instructions

First, in the terminal, create the program by simply sending ```make``` on root of the project, then the program will be created.
To run the program, besides ```./codexion```, you have to insert other 8 arguments:

- **number_of_coders** = Quantity of coders on the table, it can be from 1 or more.
- **time_to_burnout** (in miliseconds) = If a coder doesn't compile within *time_to_burnout* miliseconds since their last compilation, they'll burn out.
- **time_to_compile** (in miliseconds) = The time a coder will take to compile, after getting both dongles.
- **time_to_debug** (in miliseconds) = The time a coder will take to debug, right after they compile.
- **time_to_refactor** (in miliseconds) = The time a coder will take to refactor, right after they debug.
- **number_of_compiles_required** = Quantity of how many compilations every coder have to do during the simulation
- **dongle_cooldown** (in miliseconds) = It's the time a dongle will be **unavailable** to use after being released.
- **scheduler** = It's the policy to decide which coder will get the dongle when multiple coders request the same dongle. It have to be either "fifo" or "edf", anything else the program won't start

### Examples

```shell
./codexion 5 2000 200 200 200 7 50 edf
```

```shell
./codexion 10 800 210 20 50 5 0 fifo
```

# Resources

To understand better how therads work and how it's written in the code, I researched and read many Philosophers guides and repositories, an another 42's project (from the old Common Core) that also utilized the pthreads, specially [this guide for Philosophers](https://github.com/DeRuina/philosophers) and [this video about threads in general](https://www.youtube.com/watch?app=desktop&v=d9s_d28yJq0).
For this project I have utilized AI to check if there's any bugs or small detail that I've forgotten and clarify me better about threads and heaps.

### Fun Fact

This project is inspired on another 42's project called "Philosophers", which instead of coders it was philosophers, and instead of USB dongles it was forks.

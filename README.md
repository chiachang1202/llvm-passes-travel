# llvm-passes-travel
A simple LLVM passes playground which are inspired by NTHU Advanced Compiler (CS5404)
## Roadmap
1. Finish README.md Roadmap and References part.
2. Define the simple data structure.
3. Build passes via simple Makfile and develop new passes as new feature.
4. Add-on some backend or LIT or FileCheck feature
5. Replace build system via **CMake** and **Ninja**
---
## References
#### LLVM Passes
- Writing an LLVM Pass: 101, A. Warzynski, LLVM Developers’ Meeting 2019, [slides](https://llvm.org/devmtg/2019-10/slides/Warzynski-WritingAnLLVMPass.pdf), [video](https://youtu.be/ar7cJl2aBuU), [github](https://github.com/banach-space/llvm-tutor)
- Building, Testing and Debugging a Simple out-of-tree LLVM Pass, S. Guelton & A. Guinet, LLVM Developers’ Meeting 2015, [slides](https://llvm.org/devmtg/2015-10/slides/GueltonGuinet-BuildingTestingDebuggingASimpleOutOfTreePass.pdf), [video](https://youtu.be/BnlG-owSVTk), [github](https://github.com/quarkslab/llvm-dev-meeting-tutorial-2015)

#### LLVM Developers’ Meeting Slides
- 2019 Slides [slides](https://llvm.org/devmtg/2019-10/slides/)

#### Clang Overview
- An overview of Clang, S. Haastregt & A. Stulova, LLVM Developers’ Meeting 2019, [slides](https://llvm.org/devmtg/2019-10/slides/ClangTutorial-Stulova-vanHaastregt.pdf), [video](https://youtu.be/5kkMpJpIGYU)

#### Compiler Online Course
- CMU Lectures [slides](https://www.cs.cmu.edu/afs/cs/academic/class/15745-s16/www/lectures/)
- Northwestern University Alias Analysis [slides](https://users.cs.northwestern.edu/~simonec/files/Teaching/CAT/slides/AliasAnalysis.pdf)

#### LLVM Backend
- Tutorial: Creating a LLVM Backend for the cpu0 Architecture, Chen Chung-Shu [slides](http://jonathan2251.github.io/lbd/TutorialLLVMBackendCpu0.pdf)

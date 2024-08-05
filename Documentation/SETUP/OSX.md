# Working with source - OSX

## MACOS

1. Download the repo with --recursive
2. Checkout 'dev' branch
3. Execute ``git submodule init``
4. CD into the __repo root__
5. CD into ``/CPM/cpm``
6. 1\~\*Execute ``cargo build --release``
7. CD into __the repo root__
8. Execute ``./CPM/cpm/target/release/cpm init -f``
-> After this, ``'cpm.sh'`` will appear in the __repo root__, this will be the entrypoint to the buildsystem
9. Check if it's working by executing ``./cpm.sh -V`` from the __repo root__
10. Execute ``./Utlity/macOS/get_vendor.[sh/bat]``
11. Open ``__repo root__/cpm_install.json``. Locate your system. Check 'libraries' or 'osx_packages' list. Download each package with brew (macOS) or pacman (archlinux). NOTE: Some packages have to be sourced locally (CHECK STEP 10). 
12. Execute ``./cpm.sh setup -a`` - errors will appear but ignore those.
13. Execute ``./cpm.sh build -dg "make/clang"`` or ``./cpm.sh build -dg "make/gcc"``
14. Execute ``./cpm.sh build -db``
15. Run
# QUICK MPE SETUP

1. Download the repo
2. Checkout 'dev' branch
3. Execute ``git submodule init``
4. CD into the __repo root__
5. CD into ``/CPM/cpm``
6. 1\~\*Execute ``cargo build --release``
7. CD into __the repo root__
8. Execute ``.\CPM\cpm\target\release\cpm.exe init -f``
9. After this ``'cpm.[bat/sh]'`` will appear in the __repo root__, this will be the entrypoint to the buildsystem
10. Check if it's working by executing ``./cpm -v`` from the __repo root__
11. WINDOWS ONLY: Make sure to add VCPKG to your path
12. Execute ``.\Utlity\<PLATFORM>\get_vendor.[sh/bat]``
13. Open ``__repo root__/cpm_install.json`` check 'prerequisites' or 'dependencies' or 'tools' lists. Make sure to download packages and expose them in path (i.e. must be accessible when running in terminal)
14. WINDOWS ONLY: 2\~\*Execute ``./cpm setup -a`` to download packages and setup the environment
15. UNIX: open ``__repo root__/cpm_install.json``. Locate your system. Check 'libraries' or 'osx_packages' list. Download each package with brew (macOS) or pacman (archlinux). NOTE: Some packages have to be sourced localy (CHECK STEP 12). Finally, execute ``./cpm setup -a`` - errors will appear but ignore those.
16. 3\~\*Execute ``./cpm build -dg <SYSTEM_TYPE>``
    1. WINDOWS: ``./cpm build -dg "nt/msvc"``
    2. LINUX: ``./cpm build -dg "unix/clang"`` or ``./cpm build -dg "unix/gcc"``
    3. MACOS: ``./cpm build -dg "make/clang"`` or ``./cpm build -dg "make/gcc"``
17. Execute ``./cpm build -db``
18. Run

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
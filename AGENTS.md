# Repository Guidelines

## Project Structure & Module Organization
Core gameplay logic lives in the root C sources (e.g., `server.c`, `act.c`, `area*.c`). Area- and NPC-specific modules compile into `runtime/<id>/*.dll`, while shared item/data definitions reside under `zones/generic/*.itm`. Object files are staged in `.obj/` and helper utilities such as `create_*` and `start` sit at the root. Database schemas and seed data live in `storage.sql`; keep schema changes synchronized with server code that touches MySQL.

## Build, Test, and Development Commands
- `make all` – builds the main server, chatserver, helper binaries, and every runtime DLL listed at the top of the Makefile.
- `make server` / `make chatserver` – targeted rebuilds when touching core loop or chat features.
- `make clean` – removes binaries, DLLs, and temp files; run before release packaging or when switching toolchains.
- `./start` – launches `chatserver` and sequential area servers (`./server -a <id> -d`) to mimic a production shard; extend it when new areas are added.
GCC is configured for 32-bit output with MySQL client libraries, so ensure the required toolchain and `libmysqlclient` headers are installed before building.

## Coding Style & Naming Conventions
Follow K&R C with tab indentation and braces on the same line as declarations. Stick to `snake_case` for functions, globals, and structs (`do_message`, `struct player`). Keep module responsibilities tight: new gameplay systems belong in their own `*.c`/`*.h` pair. Warning-free builds are mandatory because `-Werror` is enabled; avoid non-portable extensions and keep headers idempotent.

## Testing Guidelines
There is no automated test harness. After each change, rebuild the affected binary and run the relevant area manually via `./server -a <area_id> -d` (or `./start` for full stacks). Validate database mutations against a local MySQL instance seeded with `storage.sql`. When regenerating data files (`create_weapons`, `create_armor`, etc.), run the generator, inspect the diff in `zones/*`, and document the outcome.

## Commit & Pull Request Guidelines
Recent history favors short, imperative subjects (e.g., “Modify Start script to include Labs”) with optional PR references. Group related modifications per commit, mention the subsystem in the subject when possible, and describe any data migrations in the body. PRs should include a summary, testing commands executed, linked issues or TODO entries, and screenshots/log excerpts for user-visible changes. Request reviews from owners of touched areas or tooling before merging.

#Stardard principles
- Delete unused or obsolete files when your changes make them irrelevant (refactors, feature removals, etc.), and revert files only when the change is yours or explicitly requested. If a git operation leaves you unsure about other agents' in-flight work, stop and coordinate instead of deleting.
- **Before attempting to delete a file to resolve a local type/lint failure, stop and ask the user.** Other agents are often editing adjacent files; deleting their work to silence an error is never acceptable without explicit approval.
- NEVER edit `.env` or any environment variable files—only the user may change them.
- Coordinate with other agents before removing their in-progress edits—don't revert or delete work you didn't author unless everyone agrees.
- Moving/renaming and restoring files is allowed.
- ABSOLUTELY NEVER run destructive git operations (e.g., `git reset --hard`, `rm`, `git checkout`/`git restore` to an older commit) unless the user gives an explicit, written instruction in this conversation. Treat these commands as catastrophic; if you are even slightly unsure, stop and ask before touching them. *(When working within Cursor or Codex Web, these git limitations do not apply; use the tooling's capabilities as needed.)*
- Never use `git restore` (or similar commands) to revert files you didn't author—coordinate with other agents instead so their in-progress work stays intact.
- Always double-check git status before any commit
- Keep commits atomic: commit only the files you touched and list each path explicitly. For tracked files run `git commit -m "<scoped message>" -- path/to/file1 path/to/file2`. For brand-new files, use the one-liner `git restore --staged :/ && git add "path/to/file1" "path/to/file2" && git commit -m "<scoped message>" -- path/to/file1 path/to/file2`.
- Quote any git paths containing brackets or parentheses (e.g., `src/app/[candidate]/**`) when staging or committing so the shell does not treat them as globs or subshells.
- When running `git rebase`, avoid opening editors—export `GIT_EDITOR=:` and `GIT_SEQUENCE_EDITOR=:` (or pass `--no-edit`) so the default messages are used automatically.
- Never amend commits unless you have explicit written approval in the task thread.

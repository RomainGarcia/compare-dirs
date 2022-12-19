# Compare directories

A simple tool used to compare the MD5 hashes of files in two directories. The first one is considered as the original one, 
the second one as the one to compare. If there is a difference between two files or if the file is not present in the 
original directory, their paths are printed out.

The tool based its comparison on the file paths, so the directories must have the same structure.

## Usage

```bash
compare-dirs <original-dir> <dir-to-compare> [-a]

-a: print all files, even if they are the same
```

## Example

```bash
./compare-dirs ../tests/wordpress-6.0.1_original/ ../tests/wordpress-6.0.1_edited/

File not present in original directory: wordpress/malware.php
File modified: wordpress/index.php

Files in original directory: 2889
Files in edited directory: 2890
Edited files found: 1
Files not found: 1
```

## Build

```bash
git clone https://github.com/RomainGarcia/compare-dirs.git
cd compare-dirs
cmake . -DCMAKE_BUILD_TYPE=release -B cmake-build
cd cmake-build
make
```

## License

Author: Romain Garcia

Copyright 2022, Romain Garcia

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at: [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

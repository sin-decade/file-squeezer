## YaFileSqueezer

![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/YaCodeLab/YaFileSqueezer?include_prereleases)
![GitHub last commit](https://img.shields.io/github/last-commit/YaCodeLab/YaFileSqueezer)
![GitHub issues](https://img.shields.io/github/issues-raw/YaCodeLab/YaFileSqueezer)
![GitHub pull requests](https://img.shields.io/github/issues-pr/YaCodeLab/YaFileSqueezer)
![GitHub](https://img.shields.io/github/license/YaCodeLab/YaFileSqueezer)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/5f24ce325e204fe285de8d04e712d671)](https://www.codacy.com/gh/YaCodeLab/YaFileSqueezer/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=YaCodeLab/YaFileSqueezer&amp;utm_campaign=Badge_Grade)

**YaFileSqueezer** is a unique file archiver designed for research and experimentation with different compression algorithms. Unlike other archiving tools, YaFileSqueezer provides users with the ability to manually adjust parameters such as sliding window size and character length to see how they impact compression quality. Additionally, the tool offers a real-time visualization of compression operations, providing users with a better understanding of how different algorithms work. While file compression is a primary feature, YaFileSqueezer's main goal is to provide a platform for experimentation and learning about compression algorithms, making it an ideal tool for researchers and students in the field.

### Contributing

This project is open for contribution from other people who have more knowledge in this area. If you're interested in contributing, please contact [YaRiabtsev](https://github.com/YaRiabtsev) or open an [issue](https://github.com/YaCodeLab/YaFileSqueezer/issues/new/choose) on the GitHub repository.

To get involved/development it is recommended to read the documentation and [configure the environment](https://community.kde.org/Get_Involved/development) according to the specified steps.

After that, you can use the following commands to install and run:
```bash
cmake -B build/ -DCMAKE_INSTALL_PREFIX=$HOME/kde/usr/
cmake --build build/
cmake --install build/

source build/prefix.sh # located in the build directory
YaFileSqueezer
```
### License

This project is licensed under the GNU General Public License v3.0.

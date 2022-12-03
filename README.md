# Gold Digger
An internal offset dumper for CS:GO

### How to use:
- Put `config.json` in the same folder as the game executable is
- Run the game
- Inject the DLL, with an injector
- Find the offset file in the same folder as config file

### config.json
Please use the [config.json](https://github.com/frk1/hazedumper/blob/master/config.json) file provided by hazedumper, as that is the standard and the
one that the program uses as a base.

### Compilation:
Open *gold_digger.sln* and change the build config to `Release | x86` and press build.    
At the end you should receive `gold_digger.dll`

## Credits:
- [frk1](https://github.com/frk1) on [hazedumper](https://github.com/frk1/hazedumper/)
- [nlohmann](https://github.com/nlohmann) on [json](https://github.com/nlohmann/json)

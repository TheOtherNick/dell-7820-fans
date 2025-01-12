# dell-7820-fans
Dell Precision Workstation 7820 Fan Tools

### Compiling
Compile program:

```
gcc dell_7820_fan_tools.c -o dell_7820_fan_tools
```
Or, use `build.sh` (does above, and runs binary afterwards).


### Usage

Read fans: 
```
sudo ./dell_7820_fan_tools
```

Set low fan speed for rear fans:
```
sudo ./dell_7820_fan_tools rear low
```

Fan options:
- `rear` - rear case fans
- `sys` - front case fans
- `cpu` - CPU fans

Speed options:
- `low` - Fans run at low speed
- `high` - Fans run at high speed


### Other remarks...
When playing with fan speeds in a Dell (atleast in the Precision 7820), CPU fan
speed is limited to Off/Low/High speeds.  Still working on determining if there
is any where to see if there is a better way to control speeds...  

Thanks to [beikesea:dell-7280-fans](https://github.com/beikesea/dell-7820-fans) for the
original work into tweaking speeds.

Note on development and other resources can be found in [./RESEARCH-NOTES.md](RESEARCH-NOTES.md).  Note, this file is considered to be very dirty (no formatting/salient thoughts/etc).

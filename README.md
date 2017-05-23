## euler
A command line utility that converts euler angles to quaternions and rotation matrices. 

## Usage
```
$ euler [-r | --radians] [-i | --intrinsic | -e | --extrinsic]
        [-a | --active | -p | --passive] [-s S | --sequence=S]
        -- ANGLE ANGLE ANGLE

Calculates rotation matrix and quaternion for given Euler angle sequence.

Examples:
        euler -- 20 -10 35
        euler -ep -- 11.1 23.9 -129.4
        euler -ea -s yzy -- 41.2 -55.5 -97.8
        euler -p -s zxy -- -176.234 -0.231 44.399
        euler -rpi -s xzx -- 0.21 1.16 -2.81

    -h, --help
        Print help and exit
    -r, --radians
        Use radians instead of degrees for input angles (default: false)
    -i, --intrinsic
        Use intrinsic elemental rotations (incompatible with -e; default: true)
    -e, --extrinsic
        Use extrinsic elemental rotations (incompatible with -i; default: false)
    -a, --active
        Specify an active rotation (incompatible with -p; default: true)
    -p, --passive
        Specify a passive rotation (incompatible with -a; default: false)
    -s, --sequence
        The rotation sequence (possible values: xyz, xzy, yxz, yzx, zxy, zyx,
        xyx, xzx, yxy, yzy, zxz, zyz; default: xyz)
```

## Examples
The default settings assume the rotation is composed intrinsically, represents an active rotation, and uses the "xyz" sequence:
```
$ euler -- 20 -10 35

Rotation Matrix:
  0.8067 -0.5649 -0.1736
  0.4903  0.8038 -0.3368
  0.3298  0.1866  0.9254

Quaternion:
 w:  0.9402
 x:  0.1392
 y: -0.1339
 z:  0.2806
```
Flags modify the default parameters; for example, one can instead specify that the rotation is composed extrinsically:
```
$ euler -e -- 20 -10 35

Rotation Matrix:
  0.8067 -0.5876  0.0625
  0.5649  0.7357 -0.3738
  0.1736  0.3368  0.9254

Quaternion:
 w:  0.9311
 x:  0.1908
 y: -0.0298
 z:  0.3094
```
All configurable parameters can be explicitly provided. For example, below is an extrinsically composed, passive rotation using the "yzy" sequence:
```
$ euler -ep -s yzy -- 11 -76 -143.2231

Rotation Matrix:
 -0.0760 -0.9525  0.2950
 -0.7772  0.2419  0.5809
 -0.6247 -0.1851 -0.7586

Quaternion:
 w:  0.3191
 x: -0.6002
 y:  0.7205
 z:  0.1373
```
If desired, the input angles can be specified in radians and using scientific notation; for example:
```
$ euler -rpi -s xzx 2.35e-1 1.16 2.81

Rotation Matrix:
  0.3993  0.8916  0.2135
  0.8669 -0.4430  0.2287
  0.2985  0.0937 -0.9498

Quaternion:
 w: -0.0404
 x:  0.8355
 y:  0.5262
 z:  0.1532
```

## Installation
[Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) is a dependency of euler and must be installed.
```
$ git clone https://github.com/kam3k/euler.git
$ cd euler
$ mkdir build && cd build
$ cmake ..
$ make
$ sudo make install
```

## Technical Background
Coming soon.

### Motivation
Coming soon.

### Intrinsic vs. Extrinsic
Coming soon.

### Active vs. Passive
Coming soon.

## FAQ
### I have roll, pitch, and yaw. Which parameters do I use?
Coming soon.
### What are "classical" Euler angles? And what are Tait-Bryan angles?
Coming soon.
### Why did you pick intrinsic, active, and "xyz" as the default parameters?
Coming soon.
# euler
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

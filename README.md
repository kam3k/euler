## euler
A command line utility that converts euler angles to quaternions and rotation matrices.

## Contents
* [Usage](#usage)
* [Examples](#examples)
* [Installation](#installation)
* [Technical Background](#technical-background)
    * [Motivation](#motivation)
    * [Intrinsic vs. Extrinsic](#intrinsic-vs-extrinsic)
    * [Active vs. Passive](#active-vs-passive)
* [FAQ](#faq)
    * [I have roll, pitch, and yaw. Which parameters do I use?](#i-have-roll-pitch-and-yaw-which-parameters-do-i-use)
    * [What are "classical" Euler angles? And what are Tait-Bryan angles?](#what-are-classical-euler-angles-and-what-are-tait-bryan-angles)
    * [Why did you pick intrinsic, active, and "zyx" as the default parameters?](#why-did-you-pick-intrinsic-active-and-zyx-as-the-default-parameters)


## Usage
The `--help` flag displays the usage below:
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
        xyx, xzx, yxy, yzy, zxz, zyz; default: zyx)
```

## Examples
The default settings assume the rotation is composed intrinsically, represents an active rotation, and uses the "zyx" sequence:
```
$ euler -- 20 -10 35

Rotation Matrix:
  0.9254 -0.3738  0.0625
  0.3368  0.7357 -0.5876
  0.1736  0.5649  0.8067

Quaternion:
 w:  0.9311
 x:  0.3094
 y: -0.0298
 z:  0.1908
```
Flags modify the default parameters; for example, one can instead specify that the rotation is composed extrinsically:
```
$ euler -e -- 20 -10 35

Rotation Matrix:
  0.9254 -0.3368 -0.1736
  0.1866  0.8038 -0.5649
  0.3298  0.4903  0.8067

Quaternion:
 w:  0.9402
 x:  0.2806
 y: -0.1339
 z:  0.1392
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
This section provides some background information on the conventions used convert Euler angles into other rotation parameterizations. That is, it explains what the flags mean in the [usage](#usage) section.

### Motivation
Euler angles can be really frustrating to use. This is evident when you examine the flags in the [usage](#usage) section above. For example, suppose you are provided three Euler angles, with no other context. There are 24 different ways to use these angles to create a rotation matrix (12 sequences each for intrinsic and extrinsic elemental rotations) and the resulting rotation matrix can represent either an active or passive rotation. Although providing no context is (hopefully) a rare occurence, it is exceedingly common that not enough information is provided to narrow things down to a single rotation matrix. (The omission of intrinsic vs. extrinsic is often the problem.) Even worse, there appears to be some conflicts in the language used to describe Euler angles, where the "xyz" sequence used one person is the "zyx" sequence used by someone else. As a result, it is useful to have a tool that can not only be used to convert Euler angles into rotation matrices and unit quaternions, but also can be used to quickly test several conventions to determine which convention someone is using.

### Intrinsic vs. Extrinsic
Coming soon.

### Active vs. Passive
Coming soon.

### Combinations of Intrinsic, Extrinsic, Active, and Passive

### Other Conventions

## FAQ

### I have roll, pitch, and yaw. Which parameters do I use?
Coming soon.

### What are "classical" Euler angles? And what are Tait-Bryan angles?
Some people use the name "Tait-Bryan" angles to describe Euler angles whose sequences consist of three different axes (i.e., xyz, xzy, yxz, yzx, zxy, zyx) and "classical" Euler angles to describe Euler angles whose sequences consist of only two different axes (i.e., xyx, xzx, yxy, yzy, zxz, zyz).

### Why did you pick intrinsic, active, and "zyx" as the default parameters?
Intrinsic and active were selected as the default parameters to match the parameters used in the [Wikipedia section](https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix) on creating a rotation matrix from Euler angles. "zyx" was selected as the default sequence because intrinsic, active rotations using these sequence are commonly used in aerospace applications (which is the background of euler's author).

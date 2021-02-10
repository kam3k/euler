## euler
A command line utility that converts euler angles to rotation matrices and quaternions.

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
Usage: euler [-r | --radians] [-e | --extrinsic] [-p | --passive]
             [-s S | --sequence=S] -- ANGLE ANGLE ANGLE

Calculates rotation matrix and quaternion for given Euler angle sequence.
The rotation matrix pre-multiplies vectors in a right-handed coordinate frame.
By default the sequence of angles are intepreted to be in degrees and are applied
in intrinsic order using the zyx sequence.

Examples:
    euler -- 20 -10 35
    euler --extrinsic --passive -- 11.1 23.9 -129.4
    euler --extrinsic --sequence yzy -- 41.2 -55.5 -97.8
    euler --passive --sequence zxy -- -176.234 -0.231 44.399
    euler --radians --passive --extrinsic --sequence xzx -- 0.21 1.16 -2.81

    -h, --help
        Print help and exit
    -r, --radians
        Use radians rather than degrees for input angles
    -e, --extrinsic
        Use extrinsic rather than intrinsic elemental rotations
    -p, --passive
        Specify a passive rather than active rotation
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
$ euler --extrinsic -- 20 -10 35

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
$ euler --extrinsic --passive --sequence yzy -- 11 -76 -143.2231

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
$ euler --radians --passive --sequence xzx -- 2.35e-1 1.16 2.81

Rotation Matrix:
  0.3993  0.8916  0.2135
  0.8669 -0.4430  0.2287
  0.2985  0.0937 -0.9498

Quaternion:
  w:  0.0404
  x: -0.8355
  y: -0.5262
  z: -0.1532
```

## Installation
```
$ git clone https://github.com/kam3k/euler.git
$ cd euler
$ mkdir build && cd build
$ cmake ..
$ make
$ sudo make install
```

## Technical Background
This section provides some background information on the conventions used convert Euler angles into other rotation parameterizations. This helps explain what the flags mean in the [usage](#usage) section.

### Motivation
Euler angles can be really frustrating to use because they are often imprecisely defined. For example, suppose you are provided three Euler angles, with no other context. There are 24 different ways to use these angles to create a rotation matrix (12 sequences each for intrinsic and extrinsic elemental rotations) and the resulting rotation matrix can represent either an active or passive rotation. Although providing no context is (hopefully) a rare occurence, it is exceedingly common that not enough information is provided to narrow things down to a single rotation matrix. (The omission of intrinsic vs. extrinsic is often the problem.) Even worse, there appears to be some conflicts in the language used to describe Euler angles, where the "xyz" sequence used by one person is the "zyx" sequence used by someone else. As a result, it is useful to have a tool that can not only be used to convert Euler angles into rotation matrices and unit quaternions, but also can be used to quickly test several conventions to determine which convention someone is using.

### Intrinsic vs. Extrinsic
Imagine the coordinate axes of two reference frames initially sitting right on top of each other (sharing the same origin and orientation). Let's call one of these the "fixed" frame and the other the "mobile" frame. Now suppose I said "rotate the mobile frame 30 degrees about the x-axis". Well, assuming the right-hand rule, this is unambiguous. Now suppose I said "next, rotate the mobile frame 15 degrees about the z-axis". Now we have an ambiguity: do I mean the z-axis of the fixed frame or the mobile frame?

When you always choose the fixed frame axes, you are said to be constructing a rotation *extrinsically*. Conversely, when you always choose the mobile frame axes, you are said to be constructing a rotation *intrinsically*. Any rotation can be achieved by a sequence of three intrinsic or extrinsic rotations (as long as consecutive rotations are about different axes).

Interestingly (and this is often a point of confusion), you get the same result if you take an extrinsic sequence of rotations and apply them in the reverse-order intrinsically (and vice-versa). For example, suppose you rotated first about the x-axis by angle *a*, then about the fixed y-axis by angle *b*, and finally about the fixed z-axis by angle *c*. This is an extrinsic "xyz" sequence. You would get the same result if you instead performed an intrinsic "zyx" sequence; that is, first rotated about the z-axis by angle *c*, then about the new mobile y-axis by angle *b*, then about the new mobile x-axis by angle *a*. For angles of 10, -25, and 30 degrees for angles *a*, *b*, and *c*, respectively, the command line arguments passed to euler for these two cases is shown below. See [this excellent tutorial](https://www.mecademic.com/resources/Euler-angles/Euler-angles) by Mecademic for more details.
```
$ euler --extrinsic --sequence xyz -- 10 -25 30
$ euler --sequence zyx -- 30 -25 10
```
In both cases, the resulting rotation matrix and quaternion are:
```
Rotation Matrix:
  0.7849 -0.5560 -0.2736
  0.4532  0.8162 -0.3585
  0.4226  0.1574  0.8925

Quaternion:
  w:  0.9346
  x:  0.1380
  y: -0.1862
  z:  0.2699
```
Using the terms *intrinsic* or *extrinsic* only matter during construction of a rotation from a sequence of Euler angles. Put differently, once you have the final result, it doesn't make sense to say that a rotation is "intrinsic" or "extrinsic"; rather, these terms tell you how it was constructed from the given Euler angles.

### Active vs. Passive
One way to view a rotation is as an operation on an object (e.g., a point in space). This operation transforms the coordinates of the object into new coordinates in the same reference frame. A rotation viewed in this way is called an *active* rotation. Another way to view a rotation is as an operation on a reference frame. This operation leaves objects alone, but rotates the reference frame in which their coordinates are measured. A rotation viewed in this way is called a *passive* rotation. 

Active and passive rotations are the inverse of each other. When parameterizing a rotation as a rotation matrix, the inverse rotation is simply the transpose of the matrix. As a result, if a rotation matrix **R** represents an active rotation, its transpose **R**<sup>T</sup> is the passive representation of the rotation. You can think of it this way: if you apply the **R** in this example to a point, you are changing the coordinates of the point. Then, if you were to apply **R**<sup>T</sup> to the rotated point, you can view this as rotating the reference frame in such a way that the original coordinates of the point are restored.

### Comparison of Intrinsic, Extrinsic, Active, and Passive
To summarize the above two sections, intrinsic/extrinsic tells you how a rotation was *constructed*, and active/passive tells you what the rotation *represents*. This section shows how the different combinations of these parameters are related. Let **R**(a₁, b₂, c₃) be an *active* rotation matrix constructed *intrinsically* by applying the Euler angles a, b, and c about axes 1, 2, and 3, respectively. The following table describes how one would modify **R**(a₁, b₂, c₃) when other conventions are used.

&nbsp;      | Intrinsic                     | Extrinsic
---         | ---                           | ---
**Active**  | **R**(a₁, b₂, c₃) 		        | **R**(c₃, b₂, a₁)
**Passive** | **R**(a₁, b₂, c₃)<sup>T</sup> | **R**(c₃, b₂, a₁)<sup>T</sup>

### Other Conventions
As stated in euler's [usage](#usage), the calculated rotation matrices *pre-multiply* column vectors (as opposed to *post-multiplying* row vectors). Furthermore, euler uses a *right-handed* coordinate system and the right hand rule is used to interpret the sign of the provided Euler angles.

## FAQ

### I have yaw, pitch, and roll. Which parameters do I use?
Most commonly, these angles represent an *intrinsic* rotation using the *zyx* sequence. See the [Active vs. Passive](#active-vs-passive) section to determine if you want an active or passive rotation.

### What are "classical" Euler angles? And what are Tait-Bryan angles?
Some people use the name "Tait-Bryan" angles to describe Euler angles whose sequences consist of three different axes (i.e., xyz, xzy, yxz, yzx, zxy, zyx) and "classical" Euler angles to describe Euler angles whose sequences consist of only two different axes (i.e., xyx, xzx, yxy, yzy, zxz, zyz).

### Why did you pick intrinsic, active, and "zyx" as the default parameters?
Intrinsic and active were selected as the default parameters to match the parameters used in the [Wikipedia section](https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix) on creating a rotation matrix from Euler angles. "zyx" was selected as the default sequence because intrinsic, active rotations using this sequence are commonly used in aerospace applications (which is the background of euler's author).

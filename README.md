# Schroedinger1D

## Schroedinger equation
With some physical constants being neglected, this program solves the following Schroedinger equation:

<img src="https://latex.codecogs.com/svg.latex?\left[-\frac{1}{2}\frac{\mathrm{d}^2}{\mathrm{d}x^2}&plus;V(x)&space;\right&space;]\psi(x)&space;=&space;E\psi(x).">

The potential **V(x)** has the periodicity of width 1, therefore it can be represented by the sum of sine and cosine functions:

<img src="https://latex.codecogs.com/svg.latex?V(x)=\sum_{n=0}^\infty&space;\Bigl[a_n\cos(2\pi&space;n&space;x)&space;&plus;b_n\sin(2\pi&space;nx)\Bigr].">

The eigenstate **&psi;(x)** should be specified by a wave vector **k**:

<img src="https://latex.codecogs.com/svg.latex?\psi(x&plus;1)=e^{\mathrm{i}k}\psi(x).">

## Conversion to N &times; N matrix

We split the one period \[0,1\] into **N** meshes, and introduce discretized wave function **&psi;<sub>n</sub>** and potential **V<sub>n</sub>**:

<img src="https://latex.codecogs.com/svg.latex?\psi_n=\psi\left(\frac{n}{N}&space;\right&space;),\&space;V_n=V\left(&space;\frac{n}{N}\right&space;)\&space;.">

The second derivative can be approximated by differenciation, and we get the following equation:

<img src="https://latex.codecogs.com/svg.latex?-\frac{N^2}{2}\Bigl(\psi_{n&plus;1}-2\psi_{n}&plus;\psi_{n-1}\Bigr)&plus;V_n\psi_n=E\psi_n.">

The periodic property can be interperted as the following equations:

<img src="https://latex.codecogs.com/svg.latex?\psi_{-1}=e^{-\mathrm{i}k}\psi_{N-1},\&space;\&space;\psi_N=e^{\mathrm{i}k}\psi_0.">

Therefore, we get the following matrix Hamiltonian **H(k)** and eigenvalue equation:

<img src="https://latex.codecogs.com/svg.latex?H(k)=\begin{pmatrix}&space;N^2&plus;V_0&space;&&space;-N^2/2&space;&&space;0&space;&0&space;&&space;\cdots&space;&&space;0&space;&&space;0&&space;-N^2e^{-\mathrm{i}k}/2\\&space;-N^2/2&space;&&space;N^2&plus;V_1&space;&&space;-N^2/2&space;&&space;0&space;&&space;\cdots&space;&&space;0&space;&&space;0&space;&&space;0&space;\\&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;\\&space;0&space;&&space;0&space;&&space;0&space;&&space;0&space;&&space;\cdots&space;&&space;-N^2/2&space;&&space;N^2&plus;V_{N-2}&space;&&space;-N^2/2&space;\\&space;-N^2e^{\mathrm{i}k}/2&space;&&space;0&space;&&space;0&space;&&space;0&space;&&space;\cdots&space;&&space;0&space;&&space;-N^2/2&space;&&space;N^2&plus;V_{N-1}&space;\end{pmatrix}">

<img src="https://latex.codecogs.com/svg.latex?H(k)\begin{pmatrix}&space;\psi_0&space;\\&space;\psi_1&space;\\&space;\vdots&space;\\&space;\psi_{N-1}\end{pmatrix}=E\begin{pmatrix}&space;\psi_0&space;\\&space;\psi_1&space;\\&space;\vdots&space;\\&space;\psi_{N-1}\end{pmatrix}.">

The Hamiltonian **H(k)** is Hermite, so we can solve the eigenvalue equation by **zheev** routine in the LAPACK package.

## Usage
```
./Schroedinger.o INPUT_FILE
```
When ```INPUT_FILE``` is not specified, **input.dat** is used as the input.

## Input file
In each line, characters after several variable necessary as the input are neglected, so you can freely write comments.

### l. 1: Number of potential components
```
2 # nn: Number of 'n's in the potential V(x)
```
The first line specifies the number of 'n's necessary for the potential **V(x)**.
If the potential can be represented by **cos(2&pi;nx)** and **sin(2&pi;nx)**, the number of 'n's is **1** (also see the following description of potential coefficients).

### ll. 2 - (nn+1): potential coefficients
```
0 1.0 0.0 # n a_n b_n
2 2.0 3.0 # n a_n b_n
```
The following **nn** lines specify the potential coefficients.
Each line is for one value of 'n' (specified by the first number), and the following two numbers represent **a<sub>n</sub>** (the coefficient for **cos(2&pi;nx)** and **b<sub>n</sub>** (the coefficient for **sin(2&pi;nx)**).
The above example means **1+2cos(4&pi;x)+3sin(4&pi;x)**.

### l. nn+2: Number of meshes
```
100 # N: Number of meshes in the range [0,1]
```
This line specify how many pieces the periodic range \[0,1\] is split into.
This value also determines the dimension of the Hamiltonian matrix and the eigenvectors.

### l. nn+3: k points
```
-0.5 0.5 100 # k_start k_end splits
```
This line specifies the k points for which eigenvalues and eigenvectors are calculated.
The input k coordinates are in unit of **2&pi;** i.e. &pm;0.5 mean the Burillouin zone boundaries.
This program calculates for **splits+1** k points.
**k\[0\]=2&pi;&times;k_start**, **k\[splits\]=2&pi;&times;k_end**, and the others are put between **k_start** and **k_end** with the same distance.

### l. nn+4: Number of eigenstates to be output
```
10 # Neigen: Number of eigenstates to be output
```
This line specifies how many eigenstates and eigenvectors are written in the output file.
**Neigen** should not be larger than **N**.

### l. nn+4: eigenvalue file
```
energy.dat # eigenvalue file
```
This line specifies one output file name.
In this output file, eigenvalues are written in the following format.
```
# Eigenvalues
# k E_1 E_2 ... E_Neigen
0.0 1 2 ... 10
0.1 2 3 ... 11
```

### l. nn+5: eigenstate file format
```
states_%d.dat # format for eigenstate files
```
This line specifies the format for eigenstate files.
This format must have **%d**, which will be replaced by the index of the k point (between 0 and k_end).
In the eigenstate file for one k point, eigenstates (normalized in the range \[0,1\]) are written in the following format.
```
# Eigenstates
# k = 0.00
# x Re(psi_1) Im(psi_1) Re(psi_2) Im(psi_2) ... Re(psi_Neigen) Im(psi_Neigen)
0.00 0.0 0.0 1.0 0.0 ... 10.0 0.0
0.01 1.0 0.0 2.0 0.1 ... 11.0 0.0
```

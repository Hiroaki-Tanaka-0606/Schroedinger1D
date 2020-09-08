# Schroedinger1D

## Schroedinger equation
With some physical constants being neglected, this program solves the following Schroedinger equation:

<img src="https://latex.codecogs.com/svg.latex?\left[-\frac{1}{2}\frac{\mathrm{d}^2}{\mathrm{d}x^2}&plus;V(x)&space;\right&space;]\psi(x)&space;=&space;E\psi(x).">

The potential **V(x)** has the periodicity of width 1, therefore it can be represented by the sum of sine and cosine functions:

<img src="https://latex.codecogs.com/svg.latex?V(x)=\sum_{n=0}^\infty&space;\Bigl[a_n\cos(2\pi&space;n&space;x)&space;&plus;b_n\sin(2\pi&space;nx)\Bigr].">

The eigenstate **&psi;(x)** should be specified by a wave vector **k**:

<img src="https://latex.codecogs.com/svg.latex?\psi(x&plus;1)=e^{\mathrm{i}k}\psi(x).">

## Conversion to N &times; N matrix

We split the one period [0,1] into **N** meshes, and introduce discretized wave function **&psi;<sub>n</sub>** and potential **V<sub>n</sub>**:

<img src="https://latex.codecogs.com/svg.latex?\psi_n=\psi\left(\frac{n}{N}&space;\right&space;),\&space;V_n=V\left(&space;\frac{n}{N}\right&space;)\&space;.">

The second derivative can be approximated by differenciation, and we get the following equation:

<img src="https://latex.codecogs.com/svg.latex?-\frac{N^2}{2}\Bigl(\psi_{n&plus;1}-2\psi_{n}&plus;\psi_{n-1}\Bigr)&plus;V_n\psi_n=E\psi_n.">

The periodic property can be interperted as the following equations:

<img src="https://latex.codecogs.com/svg.latex?\psi_{-1}=e^{-\mathrm{i}k}\psi_{N-1},\&space;\&space;\psi_N=e^{\mathrm{i}k}\psi_0.">

Therefore, we get the following matrix Hamiltonian **H(k)** and eigenvalue equation:

<img src="https://latex.codecogs.com/svg.latex?H(k)=\begin{pmatrix}&space;N^2&plus;V_0&space;&&space;-N^2/2&space;&&space;0&space;&0&space;&&space;\cdots&space;&&space;0&space;&&space;0&&space;-N^2e^{-\mathrm{i}k}/2\\&space;-N^2/2&space;&&space;N^2&plus;V_1&space;&&space;-N^2/2&space;&&space;0&space;&&space;\cdots&space;&&space;0&space;&&space;0&space;&&space;0&space;\\&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;&&space;\ddots&space;\\&space;0&space;&&space;0&space;&&space;0&space;&&space;0&space;&&space;\cdots&space;&&space;-N^2/2&space;&&space;N^2&plus;V_{N-2}&space;&&space;-N^2/2&space;\\&space;-N^2e^{\mathrm{i}k}/2&space;&&space;0&space;&&space;0&space;&&space;0&space;&&space;\cdots&space;&&space;0&space;&&space;-N^2/2&space;&&space;N^2&plus;V_{N-1}&space;\end{pmatrix}">

<img src="https://latex.codecogs.com/svg.latex?H(k)\begin{pmatrix}&space;\psi_0&space;\\&space;\psi_1&space;\\&space;\vdots&space;\\&space;\psi_{N-1}\end{pmatrix}=E\begin{pmatrix}&space;\psi_0&space;\\&space;\psi_1&space;\\&space;\vdots&space;\\&space;\psi_{N-1}\end{pmatrix}">

The Hamiltonian **H(k)** is Hermite, so we can solve the eigenvalue equation by **zheev** routine in the LAPACK package.

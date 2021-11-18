#pragma once
#include "FluidCube.h"
namespace Physics {

	FluidCube* FluidCubeCreate(int size, int diffusion, int viscosity, float dt);
	void FluidCubeFree(FluidCube* cube);
	static void set_bnd(int b, float* x, int N);
	static void lin_solve(int b, float* x, float* x0, float a, float c, int iter, int N);
	static void diffuse(int b, float* x, float* x0, float diff, float dt, int iter, int N);
	static void advect(int b, float* d, float* d0, float* velocX, float* velocY, float* velocZ, float dt, int N);
	static void project(float* velocX, float* velocY, float* velocZ, float* p, float* div, int iter, int N);
	void FluidCubeStep(FluidCube* cube);
	void FluidCubeAddDensity(FluidCube* cube, int x, int y, int z, float amount);
	void FluidCubeAddVelocity(FluidCube* cube, int x, int y, int z, float amountX, float amountY, float amountZ);
	void RunDemo(FluidCube* cube);
	void Init(FluidCube* cube);
}


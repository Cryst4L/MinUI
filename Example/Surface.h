#pragma once

#include <algorithm>

#include "../MinUI/Types.h"

//#define ISOMETRIC

using std::cos; 
using std::sin;

typedef unsigned char BYTE;

class Vector3D
{
	float m_data[3];

	public:

	float& operator()(int i)
	{
		return m_data[i];
	} 
};

class Matrix3D
{
	float m_data[3][3];

	public:

	float& operator()(int i, int j)
	{
		return m_data[i][j];
	}

	Vector3D operator*(Vector3D& v)
	{
		Vector3D r;
		for (int i = 0; i < 3; i++)
		{
			float acc = 0;
			for (int j = 0; j < 3; j++)
				acc += m_data[i][j] * v(j);
			r(i) = acc;
		}
		return r;
	}
	
	Matrix3D operator*(Matrix3D& m)
	{
		Matrix3D r;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				float acc = 0;
				for (int k = 0; k < 3; k++)
					acc += (*this)(i, k) * m(k, j);
				r(i, j) = acc;
			}		
		return r;
	}
};

class Surface
{
	static const int SPACING = 10;
	static const int DELTA_Z = 20;

	typedef struct { 
		float x, y; 
	} Point;

	private:

	int m_size;	
	
	float m_sigma_a, m_sigma_b;

	Matrix3D m_rot_x, m_rot_y, m_rot_z;

	bool * m_data_p;

	int  * m_depth_p;

	BYTE * m_rgb_p;

	std::vector <Vector3D> m_mesh;

	void drawLine(Vector3D a, Vector3D b)
	{
		float x = std::round(a(0));
		float y = std::round(a(1));
		float z = std::round(a(2));

		float x_end = std::round(b(0));
		float y_end = std::round(b(1));
		float z_end = std::round(b(2));

		int step_x = a(0) < b(0) ? 1 : -1;				
		int step_y = a(1) < b(1) ? 1 : -1;

		float sign = step_x * step_y;

		float slope = sign * (y_end - y) / (x_end - x);

		int step_count = abs(x_end - x) + abs(y_end - y);

		float dz = (z_end - z) / step_count;
	
		if (x == x_end && y == y_end)
			return;
	
		if (x == x_end)
		{
			step_x = 0;
			slope = 1;
		}

		float error = slope;

		while (x != x_end || y != y_end)
		{	
			if (error > 0.5) {
				y += step_y;
				error -= 1;
				z += dz;
			}

			if (error <= 0.5) {
				x += step_x;
				error += slope;
				z += dz;
			}

			int offset = x * m_size + y; // y * m_size + x
			if (x > 0 && x < m_size && y > 0 && y < m_size)	
				if (z < (m_depth_p[offset] + DELTA_Z))
					m_data_p[offset] = 1;

		}
	}


	void flatLine(int x1, int x2, int y, int v1, int v2)
	{
		if (x1 == x2)
			return;

		if (x1 > x2) {
			std::swap(x1, x2);
			std::swap(v1, v2);
		}	

		float dv = (v2 - v1) / (float) (x2 - x1);

		float v = v1 - dv; // TODO fix this: v = v1

		if (y > 0 && y < m_size)
		{
			for(int x = x1; x <= x2 ; x++, v += dv) // TODO fix this: x < x2
			{
				if (x > 0 && x < m_size)
				{
					float t = m_depth_p[x * m_size + y]; 
					if (v < t || t == 0) {
						m_depth_p[x * m_size + y] = v;
					}

				}
			}
		}
	}

	void drawTriangle(Vector3D a, Vector3D b, Vector3D c)
	{
		a(0) = round(a(0)); a(1) = round(a(1));
		b(0) = round(b(0)); b(1) = round(b(1));
		c(0) = round(c(0)); c(1) = round(c(1));

		if (a(1) > b(1)) std::swap(a, b);

		if (a(1) > c(1)) std::swap(a, c);

		if (b(1) > c(1)) std::swap(b, c);

		double dx1 = (b(0) - a(0)) / (b(1) - a(1));
		double dx2 = (c(0) - a(0)) / (c(1) - a(1));
		double dx3 = (c(0) - b(0)) / (c(1) - b(1));

		double dz1 = (b(2) - a(2)) / (b(1) - a(1));
		double dz2 = (c(2) - a(2)) / (c(1) - a(1));
		double dz3 = (c(2) - b(2)) / (c(1) - b(1));

		Vector3D s = a, e = a;

		if (dx1 > dx2) {
	
			for (; s(1) < b(1); 
				   s(1)++, e(1)++, 
				   s(0) += dx2, e(0) += dx1,
				   s(2) += dz2, e(2) += dz1)
			{	
				flatLine(s(0), e(0), s(1), s(2), e(2));
			}

	
			e = b;

			for (; s(1) < c(1); 
			       s(1)++, e(1)++, 
			       s(0) += dx2, e(0) += dx3,
			       s(2) += dz2, e(2) += dz3)
			{
				flatLine(s(0), e(0), s(1), s(2), e(2));
			}

		} else {
	
			for (; s(1) < b(1); 
			       s(1)++, e(1)++, 
			       s(0) += dx1, e(0) += dx2,
			       s(2) += dz1, e(2) += dz2)
			{
				flatLine(s(0), e(0), s(1), s(2), e(2));
			}
						
			s = b;

			for (; s(1) < c(1); 
			       s(1)++, e(1)++, 
			       s(0) += dx3, e(0) += dx2,
				   s(2) += dz3, e(2) += dz2)
			{
				flatLine(s(0), e(0), s(1), s(2), e(2));
			}
		}
	}

	void drawTile(Vector3D a, Vector3D b, Vector3D c, Vector3D d)
	{
		drawTriangle(a, b, c);
		drawTriangle(c, d, a);
	}


	// Gaussian function
	float Gaussian(float x, float y, float sigma)
	{
		float k = 1.0 / (sigma * std::sqrt(2 * M_PI));
		float e = std::exp(-((x * x) + (y * y)) / (2 * sigma * sigma)); 
		return k * e;
	}

	// Difference of Gaussian
	float expression(float x, float y) 
	{
		float a = Gaussian(x, y, m_sigma_a);
		float b = Gaussian(x, y, m_sigma_b);
		return a - b;
	}


	public:

	Surface(int size)
	: m_size(size), m_sigma_a(0.5), m_sigma_b(0.25)
	{
		m_data_p  = new bool [size * size];
		m_rgb_p   = new BYTE [3 * size * size];
		m_depth_p = new int  [size * size];

		std::fill(m_data_p, m_data_p + size * size, 0);
		std::fill(m_rgb_p, m_rgb_p + 3 * size * size, 0);
		std::fill(m_depth_p, m_depth_p + size * size, 0);
	}

	~Surface()
	{
		delete [] m_data_p; 
		delete [] m_rgb_p;
		delete [] m_depth_p;
	}

	Surface& operator=(const Surface &surface)
	{
		if (this != &surface)
		{
			m_size = surface.m_size;

			m_sigma_a = surface.m_sigma_a;
			m_sigma_b = surface.m_sigma_b;

			m_rot_x = surface.m_rot_x;
			m_rot_y = surface.m_rot_y;
			m_rot_z = surface.m_rot_z;
			
			////////////////////////////////////////////////////
			
			bool * temp_data_p = m_data_p;
			m_data_p = new bool[m_size * m_size];

			for (int i = 0; i < m_size * m_size; i++)
				m_data_p[i] = surface.m_data_p[i];
			
			delete [] temp_data_p;

			////////////////////////////////////////////////////

			int * temp_depth_p = m_depth_p;
			m_depth_p = new int[m_size * m_size];

			for (int i = 0; i < m_size * m_size; i++)
				m_depth_p[i] = surface.m_depth_p[i];
			
			delete [] temp_depth_p;
		
			////////////////////////////////////////////////////

			BYTE * temp_rgb_p = m_rgb_p;
			m_rgb_p = new BYTE[m_size * m_size];

			for (int i = 0; i < m_size * m_size; i++)
				m_rgb_p[i] = surface.m_rgb_p[i];
			
			delete [] temp_rgb_p;
		}

		return *this;
	}

	Surface(const Surface &surface) 
	{
		*this = surface; // overloaded '=' is used
	}

	void setRotX(float angle)
	{
		m_rot_x(0,0) =           1; m_rot_x(0,1) =           0; m_rot_x(0,2) =           0;
		m_rot_x(1,0) =           0; m_rot_x(1,1) =  cos(angle); m_rot_x(1,2) = -sin(angle);
		m_rot_x(2,0) =           0; m_rot_x(2,1) =  sin(angle); m_rot_x(2,2) =  cos(angle);
	}

	void setRotY(float angle)
	{
		m_rot_y(0,0) =  cos(angle); m_rot_y(0,1) =           0; m_rot_y(0,2) =  sin(angle);
		m_rot_y(1,0) =           0; m_rot_y(1,1) =           1; m_rot_y(1,2) =           0;
		m_rot_y(2,0) = -sin(angle); m_rot_y(2,1) =           0; m_rot_y(2,2) =  cos(angle);
	}

	void setRotZ(float angle)
	{
		m_rot_z(0,0) =  cos(angle); m_rot_z(0,1) = -sin(angle); m_rot_z(0,2) =           0;
		m_rot_z(1,0) =  sin(angle); m_rot_z(1,1) =  cos(angle); m_rot_z(1,2) =           0;
		m_rot_z(2,0) =           0; m_rot_z(2,1) =           0; m_rot_z(2,2) =           1;
	}
	
	void setSigmaA(float value) { m_sigma_a = value; }

	void setSigmaB(float value) { m_sigma_b = value; }

	void render(MinUI::Color& color)
	{
		// Compute the rotation matrix
		Matrix3D rotation = m_rot_x * m_rot_y * m_rot_z;

		// Populate the mesh
		m_mesh.clear();

		int nb_cols = m_size / SPACING + 1;
		int nb_rows = m_size / SPACING + 1;
		int nb_vertices = nb_cols * nb_rows;

		for (int i = 0; i < nb_rows; i++)
			for (int j = 0; j < nb_cols; j++)
			{
				Vector3D vertice;

				vertice(0) =  2 * (i * SPACING) / (float) m_size - 1; // x
				vertice(1) =  2 * (j * SPACING) / (float) m_size - 1; // y
				vertice(2) = expression(vertice(0), vertice(1));      // z

				m_mesh.push_back(vertice);
			}

		// Rotate the mesh
		for (int n = 0; n < nb_vertices; n++)
			m_mesh[n] = rotation * m_mesh[n];

		// Calibrate the point cloud
		for (int n = 0; n < nb_vertices; n++)
		{
			m_mesh[n](0) = 0.5 * (m_mesh[n](0) + 1);
			m_mesh[n](1) = 0.5 * (m_mesh[n](1) + 1);
			m_mesh[n](2) = 0.5 * (m_mesh[n](2) + 1);
		} 

		// Rescale the mesh
		for (int n = 0; n < nb_vertices; n++)
		{
			m_mesh[n](0) *= m_size;
			m_mesh[n](1) *= m_size;
			m_mesh[n](2) *= m_size;
		}

		// Clean the screen
		for (int k = 0; k < m_size * m_size; k++) {
			m_data_p[k]  = 0;	
			m_depth_p[k] = 0;
			m_rgb_p[k]   = 0;
		}

		// Fill the z buffer
		for (int i = 0; i < (nb_rows - 1); i++)
			for (int j = 0; j < (nb_cols - 1); j++)
			{
				Vector3D a = m_mesh[i * nb_cols + j];
				Vector3D b = m_mesh[i * nb_cols + j + 1];
				Vector3D c = m_mesh[(i + 1) * nb_cols + j + 1];
				Vector3D d = m_mesh[(i + 1) * nb_cols + j];
				drawTile(a, b, c, d);
			}

		// render the lines (vertical)	
		for (int i = 0; i < nb_rows; i++)
			for (int j = 0; j < (nb_cols - 1); j++)
			{
				Vector3D a = m_mesh[i * nb_cols + j];
				Vector3D b = m_mesh[i * nb_cols + j + 1];
				drawLine(a, b);
			}

		// render the lines (horizontal)	
		for (int i = 0; i < (nb_rows - 1); i++)
			for (int j = 0; j < (nb_cols); j++)
			{
				Vector3D a = m_mesh[i * nb_cols + j];
				Vector3D b = m_mesh[(i + 1) * nb_cols + j];
				drawLine(a, b);
		}

		// Fill the RGB data
		for (int k = 0; k < m_size * m_size; k++)
		{
			m_rgb_p[3 * k]     = m_data_p[k] * color.r; // color.r;
			m_rgb_p[3 * k + 1] = m_data_p[k] * color.g; //color.g;
			m_rgb_p[3 * k + 2] = m_data_p[k] * color.b; //color.b;
		}
	}

	bool * data() { return m_data_p; }

	int * depthData() { return m_depth_p; }

	BYTE * RGBData() { return m_rgb_p; }

};

/*
	void drawLine(Vector3D a, Vector3D b)
	{
		float x = std::round(a(0));
		float y = std::round(a(1)) ;

		float x_end = std::round(b(0));
		float y_end = std::round(b(1));

		int step_x = a(0) < b(0) ? 1 : -1;				
		int step_y = a(1) < b(1) ? 1 : -1;

		float sign = step_x * step_y;

		float slope = sign * (y_end - y) / (x_end - x);

		std::cout << "slope " << slope << std::endl;		

		if (x == x_end)
		{
			step_x = 0;
			slope = (y_end - y);
		}

		float error = slope;
		
		while (x != x_end || y != y_end)
		{	
			std::cout << "---------" << std::endl;
			std::cout << x << "/" << x_end << std::endl;
			std::cout << y << "/" << y_end << std::endl;

			if (error > 0.5) {
				y += step_y;
				error -= 1;
			}

			if (error <= 0.5) {
				x += step_x;
				error += slope;
			}

			//std::cout << x << " " << y << std::endl;
			int offset = y * m_size + x;
			m_data_p[offset] = 1; // round
		}
*/	

/*
	// Bresenham algorithm
	void drawLine(Point a, Point b)
	{
		int x0 = round(a.x), y0 = round(a.y);
		int x1 = round(b.x), y1 = round(b.y);

		int dx =  std::abs(x1 - x0);
		int dy = -std::abs(y1 - y0);

		int sx = x0 < x1 ? 1 : -1;				
		int sy = y0 < y1 ? 1 : -1;

		int err = dx + dy, e2;

		while (x0 != x1 || y0 != y1) {
			
			if (x0 > 0 && x0 < m_size && 
			    y0 > 0 && y0 < m_size)
			{
 				m_data_p[x0 * m_size + y0] = 1;
			}
			
			e2 = 2 * err;

			if (e2 >= dy) {
				err += dy;
				x0 += sx;
			}

			if (e2 <= dx) {
				err += dx;
				y0 += sy;
			}
		}
	}
*/


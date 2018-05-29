// RayTracingHelo.cpp : �������̨Ӧ�ó������ڵ㡣
//�ļ���������ο���https://jingyan.baidu.com/article/ac6a9a5e66c34d2b643eac66.html
//y�����ϣ�x�����ң�z����ģ�ѡ�����½�Ϊ��-2.0��-1.0��-1.0��

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "vec3.h"
#include "ray.h"
using namespace std;

float hit_sphere(const vec3& center, float radius, const ray& r) 
{
	vec3 oc = r.origin() - center;//�����Ƶ�����
	float a = dot(r.direction(), r.direction());
	float b = 2 * dot(oc,r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4 * a*c;//��Ԫһ�η����󽻵�
	if (discriminant < 0) 
	{
		return -1.0;
	}
	else 
	{
		//��������ֻ��ѡ����һ������⣬ͬʱͨ��color()���ж��Ƿ����ཻ
		return (-b - sqrt(discriminant)) / (2.0*a);//����ཻ�������ཻʱ��tֵ����Ϊʲô����(-b + sqrt(discriminant)) / (2.0*a)
	}

}
vec3 color(const ray& r) 
{
	float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	if (t > 0.0) //��������������ཻ���ڹ����������ཻ
	{//��ȡ�ཻʱ��A+t*B(�����ཻ��)�����ĵĲ�ֵ�ĵ�λ��Ϊ���ߵ�λ����
		//����ԭ[-1,1]�ĸ���λֵ����ӳ�䵽[0,1]��
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	} 
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);//��������ɨ�������ɫ

}

void main()
{
	ofstream outfile;
	outfile.open("ColorWorld.txt");
	int nx = 200;
	int ny = 100;
	outfile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);//ע�����½ǵ����ֵ���ǳ���camera��ԭ���⣬ɨ�����ڴˣ��󽻣�
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 1; i <= nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u*horizontal + v*vertical);
			vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			outfile << ir << " " << ig << " " << ib << "\n";
			
		}
	}
	outfile.close();
	return;
}


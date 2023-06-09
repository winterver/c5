int g_a;

int max(int a, int b, int c) {
	return a*b*c;
}

long* g_pb;

int main()
{
	int a=123, b=233, c=a+b;
	max(a, b, c);
	return c;
}

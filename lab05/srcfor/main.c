int main()
{
        int x = 147;
        int y = 66;
        int i; 
        int gcd;
for (i=1;i<=x&&i<=y;i++)
{ if( x%i==0 && y%i==0)
 gcd = i;
}
return gcd;
       }


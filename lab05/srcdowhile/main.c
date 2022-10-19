int main ()
{
int x = 1634;
int y = 638;
do {
if (x>y) { x=x-y;
}
else {y=y-x;}}
while (x!=y);
return x;
}

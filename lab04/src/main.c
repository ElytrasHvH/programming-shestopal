int main()
{
        double a = 0.5;

        if (a <= -1.0) {
                a = -1.0 / a;
        } else if (a<1.0 & a> - 1.0) {
                a = a * a;
        } else if (a >= 1.0) {
                a = 1.0;
        }

        return 0;
}

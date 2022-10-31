int main()
{
        float x = 0.5f; // input var
        float y; // answer var
        if (x <= -1.0f) // check first condition
        {
                y = -1.0f / x;
        } else if (x<1.0f && x> - 1.0f) // check for second condition
        {
                y = x * x;
        } else // force value if 1 & 2 conditions didnt work
        {
                y = 1.0f;
        }

        return y;
}

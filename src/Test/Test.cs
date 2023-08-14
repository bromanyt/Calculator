using SmartCalc.Model;
using Xunit;
using System.Text;
using System;
using static System.Math;

namespace src;

public class Test
{
    [Fact]
    public void ValidatorNegative()
    {
        string[] negative = {
            "2+mod1",
            "2-mod1",
            "2*mod1",
            "2/mod1",
            "2modmod1",
            "(mod2)",
            "(*mod3)",
            "mod4",
            "(2mod)",
            "(mod2mod3)",
            "(mod)",
            "(^)",
            "(*2)",
            "()",
            "(*/)",
            "(-+*/^)",
            "(.)",
            "sin()",
            "3+4()+cos",
            "2+/1",
            "2+*1",
            "2-*1",
            "2-/1",
            "2--/1",
            "2++**1",
            "2+*-1",
            "2*/1",
            "2/*1",
            "2**1",
            "2//1",
            "(*1+3)*2",
            ".2+3",
            "2..3+1",
            "23.39.94+1",
            "56.78.3455.23",
            "2.3.4+1",
            "...345+3",
            "2.+3",
            "(1+)*2",
            "*+",
            "(1+(1+))*3",
            "sin(2**3)",
            "(1+)*2",
            "(*1+3)*2",
            ".2+3",
            "2.+3",
            "2..3+1",
            "(23+(34-",
            "))24+4((",
            ")10-2(",
            "(23-4(24)(",
            "58*",
            "23+45-",
            "857*(32-45)*",
            "7*",
            "*8",
            "**8",
            "35*sin23)",
            "11-cos34+5)",
            "23(4+1)",
            "4+2(41-3)",
            "E23+4",
            "34-23E",
            "8+.E34-1",
            "73E.*12",
            "23E-E3+14",
            "87EE5*3",
            "8E6E32-11"
        };

        IntPtr calc = SmartCalculator.CreateCalculator();
        StringBuilder sb = new();
        for (int i = 0; i < 67; i++)
        {
            sb.Append(negative[i]);
            SmartCalculator.Calculate(calc, sb);
            sb.Clear();
            Assert.False(SmartCalculator.IsExpressionCorrect(calc));
        }
        SmartCalculator.FreeCalculator(calc);

    }

    [Fact]
    public void ValidatorPositive()
    {
        string[] positive = {
        "2+3",
        "2-3",
        "4*2",
        "5/3",
        "9mod10",
        "(4+5)",
        "((4-2))",
        "sin(3)+cos(34)",
        "4+(3*cos(5))-355",
        "24+(45-(sin(12))*cos(23))",
        "587*2",
        "3.456/23",
        "0.45mod32",
        "0.21^3.456023",
        "34--45",
        "-34+++---9.23",
        "sin(4+cos(34))",
        "sin(32)",
        "cos(14)",
        "atan(23+sqrt(15))",
        "34+x",
        "sin(x)",
        "x+42",
        "x+x",
        "-4+2",
        "sin(-4)",
        "-(2+5)"
    };

        IntPtr calc = SmartCalculator.CreateCalculator();
        StringBuilder sb = new();
        for (int i = 0; i < 27; i++)
        {
            sb.Append(positive[i]);
            SmartCalculator.Calculate(calc, sb);
            sb.Clear();
            Assert.True(SmartCalculator.IsExpressionCorrect(calc));
        }
        SmartCalculator.FreeCalculator(calc);
    }

    [Fact]
    public void CalculatorTest()
    {
        string[] expressions = {
            "12-11",
            "84+16",
            "2*4",
            "10/5",
            "2^3",
            "(10-2+4)*2",
            "4-(2+3)",
            "10-(2*(4+2))",
            "0.34*0.67+0.325",
            "0.45^0.3",
            "-4-2",
            "(-4+2)",
            "-(2+5)",
            "-(-cos(42))",
            "-(-cos(54-4)+2)",
            "cos(34-0.5)",
            "2234^0.03",
            "1000000000000-7890000000000",
            "212-24+98-857*3-876+98/342*4/385.1",
            "sin(90)",
            "(tan(514-9)+sin(873))+cos(876)",
            "875-tan(45)*34",           
            "cos(5+12)-sin(98)",
            "212.3+(765-cos(34-0.5)+5)"
        };

        double[] expect =
        {
            12-11,
            84+16,
            2*4,
            10/5,
            Pow(2,3),
            (10-2+4)*2,
            4-(2+3),
            10-(2*(4+2)),
            0.34*0.67+0.325,
            Pow(0.45,0.3),
            -4-2,
            (-4+2),
            -(2+5),
            -(-Cos(42)),
            -(-Cos(54-4)+2),
            Cos(34-0.5),
            Pow(2234,0.03),
            1000000000000-7890000000000,
            212.0-24.0+98.0-857.0*3.0-876.0+98.0/342.0*4.0/385.1,
            Sin(90),
            (Tan(514-9)+Sin(873))+Cos(876),
            875-Tan(45)*34,
            Cos(5+12)-Sin(98),
            212.3+(765-Cos(34-0.5)+5)
        };
        IntPtr calc = SmartCalculator.CreateCalculator();
        StringBuilder sb = new();
        for (int i = 0; i < 24; i++)
        {
            sb.Append(expressions[i]);
            SmartCalculator.Calculate(calc, sb);
            sb.Clear();
            Assert.True(SmartCalculator.IsExpressionCorrect(calc));
            double result = SmartCalculator.GetAnswer(calc);
            Assert.Equal(result, expect[i], 7);
        }
        SmartCalculator.FreeCalculator(calc);
    }


    [Fact]
    public void simpleOperations()
    {
        IntPtr sc = SmartCalculator.CreateCalculator();
        string[] expressions = {
            "99+101",
            "0.345-0.301",
            "1.1234567*320",
            "734552/2",
            "4^3",
            "7*2^2",
            "sqrt(724)",
            "log(34)",
            "ln(34)",
            "0.000004+0.000006"
        };

        double[] expect = {
            99+101,
            0.345-0.301,
            1.1234567*320,
            734552/2,
            Pow(4,3),
            7*Pow(2,2),
            Sqrt(724),
            Log10(34),
            Log(34),
            0.000004+0.000006
        };

        StringBuilder sb = new();
        for (int i = 0; i < 10; i++)
        {
            sb.Append(expressions[i]);
            SmartCalculator.Calculate(sc, sb);
            sb.Clear();
            Assert.True(SmartCalculator.IsExpressionCorrect(sc));
            double result = SmartCalculator.GetAnswer(sc);
            Assert.Equal(result, expect[i], 7);
        }
        SmartCalculator.FreeCalculator(sc);
    }

    [Fact]
    public void numberWithE()
    {
        IntPtr sc = SmartCalculator.CreateCalculator();
        string[] expressions = {
            "2.3E5*2",
            "2345E4/100",
            "7302E-4*1000",
            "0.00009E7*23",
            "5000000E-7/2",
            "sin(500E-2)+2344"
        };

        double[] expect = {
            2.3E5*2,
            2345E4/100,
            7302E-4*1000,
            0.00009E7*23,
            5000000E-7/2,
            Sin(500E-2)+2344
        };
        StringBuilder sb = new();
        for (int i = 0; i < 6; i++)
        {
            sb.Append(expressions[i]);
            SmartCalculator.Calculate(sc, sb);
            sb.Clear();
            Assert.True(SmartCalculator.IsExpressionCorrect(sc));
            double result = SmartCalculator.GetAnswer(sc);
            Assert.Equal(result, expect[i], 7);
        }
        SmartCalculator.FreeCalculator(sc);
    }

    [Fact]
    public void simpleTtigonometric()
    {
        IntPtr sc = SmartCalculator.CreateCalculator();
        string[] expressions = {
            "sin(240)",
            "cos(43456)",
            "tan(999)",
            "asin(0.5)",
            "acos(0.5)",
            "atan(162)"
        };

        double[] expect = {
            Sin(240),
            Cos(43456),
            Tan(999),
            Asin(0.5),
            Acos(0.5),
            Atan(162)
        };
        StringBuilder sb = new();
        for (int i = 0; i < 6; i++)
        {
            sb.Append(expressions[i]);
            SmartCalculator.Calculate(sc, sb);
            sb.Clear();
            Assert.True(SmartCalculator.IsExpressionCorrect(sc));
            double result = SmartCalculator.GetAnswer(sc);
            Assert.Equal(result, expect[i], 7);
        }
        SmartCalculator.FreeCalculator(sc);
    }

    [Fact]
    public void brackets()
    {
        IntPtr sc = SmartCalculator.CreateCalculator();
        string[] expressions = {
            "(0.456*3)+0.59",
            "794+(93/2)-20",
            "934-(76*3)+23^3*2",
            "(3+((45+3)-7))*3",
            "(sin(30))-(84-23*2)"
        };

        double[] expect = {
            (0.456*3)+0.59,
            794.0+(93.0/2.0)-20.0,
            934-(76*3)+Pow(23,3)*2,
            (3+((45+3)-7))*3,
            (Sin(30))-(84-23*2)
        };
        StringBuilder sb = new();
        for (int i = 0; i < 5; i++)
        {
            sb.Append(expressions[i]);
            SmartCalculator.Calculate(sc, sb);
            sb.Clear();
            Assert.True(SmartCalculator.IsExpressionCorrect(sc));
            double result = SmartCalculator.GetAnswer(sc);
            Assert.Equal(result, expect[i], 7);
        }
        SmartCalculator.FreeCalculator(sc);
    }

    [Fact]
    public void combination()
    {
        IntPtr sc = SmartCalculator.CreateCalculator();
        string[] expressions = {
            "tan(sin(45)-cos(90))",
            "845-(34+98-4^2)*(3857-3855)-(0.34/3.1)+(sin(60))",
            "((394-sin(345))+(345/0.23)/2-12mod5)*7",
            "8456*3-(atan(90)+12^2-839.35*(-34))"
        };

        double[] expect = {
            Tan(Sin(45)-Cos(90)),
            845-(34+98-Pow(4,2))*(3857-3855)-(0.34/3.1)+(Sin(60)),
            ((394-Sin(345))+(345/0.23)/2-12%5)*7,
            8456*3-(Atan(90)+Pow(12,2)-839.35*(-34))
        };
        StringBuilder sb = new();
        for (int i = 0; i < 4; i++)
        {
            sb.Append(expressions[i]);
            SmartCalculator.Calculate(sc, sb);
            sb.Clear();
            Assert.True(SmartCalculator.IsExpressionCorrect(sc));
            double result = SmartCalculator.GetAnswer(sc);
            Assert.Equal(result, expect[i], 7);
        }
        SmartCalculator.FreeCalculator(sc);
    }

    [Fact]
    public void negative()
    {
        IntPtr sc = SmartCalculator.CreateCalculator();
        string[] expressions = {
            "-34+20",
            "(-0.23+2)*71",
            "-(+34)+20",
            "25/(-cos(3))",
            "00.98+00000.02",
            "-cos(20)+-sin(34)",
            "42^(-2)"
        };

        double[] expect = {
            -34+20,
            (-0.23+2)*71,
            -34+20,
            25/(-Cos(3)),
            00.98+00000.02,
            -Cos(20)-Sin(34),
            Pow(42,(-2))
        };
        StringBuilder sb = new();
        for (int i = 0; i < 7; i++)
        {
            sb.Append(expressions[i]);
            SmartCalculator.Calculate(sc, sb);
            sb.Clear();
            Assert.True(SmartCalculator.IsExpressionCorrect(sc));
            double result = SmartCalculator.GetAnswer(sc);
            Assert.Equal(result, expect[i], 7);
        }
        SmartCalculator.FreeCalculator(sc);
    }

}
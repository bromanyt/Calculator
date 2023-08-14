using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using static System.Math;

namespace SmartCalc.Model;

public class SmartCalculator : INotifyPropertyChanged
{
    readonly static string s_path = Path.Combine(Directory.GetCurrentDirectory(), ".history.log");
    readonly static int s_pointCount = 1000;

    public double? Result { get; private set; }
    public string? Answer { get; set; } = "Your answer";
    public bool Status { get; private set; } = true;
    public List<double> CoordinateX { get; private set; } = new();
    public List<double?> CoordinateY { get; private set; } = new();
    public List<string> History { get; private set; } = new();
    public event PropertyChangedEventHandler? PropertyChanged;

    public SmartCalculator()
    {
        loadHistory();
    }

    public void CalculateExpression(StringBuilder expression)
    {
        IntPtr calc = CreateCalculator();
        Calculate(calc, expression);
        Status = IsExpressionCorrect(calc);
        if (Status)
        {
            Result = GetAnswer(calc);
            if (Result is not null)
            {
                Answer = $"{expression}={Result}";
                if (!History.Contains(Answer) && !History.Contains(expression.ToString()))
                {
                    saveHistory(Answer);
                }
            }
        }
        else
        {
            Result = null;
        }
        FreeCalculator(calc);
        OnPropertyChanged();
    }

    private void saveHistory(string expression)
    {
        using (StreamWriter sw = File.AppendText(s_path))
        {
            sw.WriteLine(expression);
            sw.Close();
        }
        History.Add(expression);
    }

    private void loadHistory()
    {
        
        if (File.Exists(s_path))
        {
            using (StreamReader sr = new(s_path))
            {
                string? line;
                while ((line = sr.ReadLine()) is not null)
                {
                    History.Add(line);
                }
                sr.Close();
            }
        }
    }

    public void ClearHistory()
    {
        if (File.Exists(s_path))
        {
            File.Delete(s_path);
            History.Clear();
            OnPropertyChanged();
        }
    }

    public void GetCoordinates(double minX, double maxX, StringBuilder function)
    {
        IntPtr calc = CreateCalculator();
        double xValue = minX;
        double step = (Abs(minX) + Abs(maxX)) / s_pointCount;

        CalculateCoordinates(calc, function, minX, step);
        Status = IsExpressionCorrect(calc);

        if (Status)
        {
            if (CoordinateX.Count > 0 || CoordinateY.Count > 0)
            {
                CoordinateX.Clear();
                CoordinateY.Clear();
            }
            GetArrayOfCoordinateY(calc, out int theSize, out IntPtr theArrayPtr);
            double[] theArray = new double[theSize];
            Marshal.Copy(theArrayPtr, theArray, 0, theSize);
            Marshal.FreeCoTaskMem(theArrayPtr);

            for (int i = 0; i < s_pointCount; i++)
            {
                CoordinateX.Add(Math.Round(xValue, 4));
                if (Double.IsInfinity(theArray[i]) || Double.IsNaN(theArray[i]))
                {
                    CoordinateY.Add(null);
                }
                else
                {
                    CoordinateY.Add(theArray[i]);
                }
                xValue += step;
            }
            string expression = function.ToString();
            if (!History.Contains(expression))
            {
                saveHistory(expression);
            }
        }
        FreeCalculator(calc);
        OnPropertyChanged();
    }

    private void OnPropertyChanged([CallerMemberName] string? propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    [DllImport("SmartCalc/Model/SmartCalc_v2/libSmC.dylib", EntryPoint = "CreateCalculator")]
    public static extern IntPtr CreateCalculator();

    [DllImport("SmartCalc/Model/SmartCalc_v2/libSmC.dylib", EntryPoint = "Calculate", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern void Calculate(IntPtr SmartCalc_v2Calculator, StringBuilder expression);

    [DllImport("SmartCalc/Model/SmartCalc_v2/libSmC.dylib", EntryPoint = "CalculateWithX", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern void CalculateWithX(IntPtr SmartCalc_v2Calculator, StringBuilder expression, StringBuilder x);

    [DllImport("SmartCalc/Model/SmartCalc_v2/libSmC.dylib", EntryPoint = "IsExpressionCorrect")]
    public static extern bool IsExpressionCorrect(IntPtr SmartCalc_v2Calculator);

    [DllImport("SmartCalc/Model/SmartCalc_v2/libSmC.dylib", EntryPoint = "GetAnswer")]
    public static extern double GetAnswer(IntPtr SmartCalc_v2Calculator);

    [DllImport("SmartCalc/Model/SmartCalc_v2/libSmC.dylib", EntryPoint = "FreeCalculator")]
    public static extern void FreeCalculator(IntPtr SmartCalc_v2Calculator);

    [DllImport("SmartCalc/Model/SmartCalc_v2/libSmC.dylib", EntryPoint = "CalculateCoordinates")]
    public static extern void CalculateCoordinates(IntPtr SmartCalc_v2Calculator, StringBuilder expression, double x_min, double step_x);

    [DllImport("SmartCalc/Model/SmartCalc_v2/libSmC.dylib", EntryPoint = "GetArrayOfCoordinateY")]
    public static extern void GetArrayOfCoordinateY(IntPtr SmartCalc_v2Calculator, out int length, out IntPtr array);
}

namespace sm4.SmartCalc.Model;

public class CalculatorData
{
    public string CurrentExpression { get; set; } = "";
    public List<string> HistoryList { get; private set; } = new();
    public string Answer { get; private set; } = "";
    public bool Status { get; private set; } = true;
    public double[] CoordinateX { get; private set; } = Array.Empty<double>();
    public double?[] CoordinateY { get; private set; } = Array.Empty<double?>();
    public Dictionary<string, double> GraphSize { get; set; } = new();

    public CalculatorData(string expression, List<string>? history, string answer = "", bool status = true)
	{
		if (history is not null)
		{
			HistoryList = history;
		}
		Answer = answer;
		Status = status;
        CurrentExpression = expression;
        GraphSize = new Dictionary<string, double> { { "xMin", -10 }, { "xMax", 10 }, { "yMin", -10 }, { "yMax", 10 } };
    }

    public CalculatorData(List<string>? history, List<double>? coordinatesX = null, List<double?>? coordinatesY = null)
    {
        if (history is not null)
        {
            HistoryList = history;
        }
        if (coordinatesX is not null && coordinatesY is not null)
        {
            CoordinateX = coordinatesX.ToArray();
            CoordinateY = coordinatesY.ToArray();

        }
        else
        {
            GraphSize = new Dictionary<string, double> { { "xMin", -10 }, { "xMax", 10 }, { "yMin", -10 }, { "yMax", 10 } };
        }
    }
}


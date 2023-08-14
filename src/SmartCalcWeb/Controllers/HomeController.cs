using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using sm4.Models;
using SmartCalc.Model;
using sm4.SmartCalc.Model;
using System.Text;
using System.Globalization;

namespace sm4.Controllers;

public class HomeController : Controller
{
    private SmartCalculator _smartCalculator = new();

    public HomeController()
    {
        CultureInfo.CurrentCulture = new CultureInfo("en-US");
    }

    public IActionResult Index()
    {
        return View(new CalculatorData(_smartCalculator.History!, null));
    }

    [Route("Home/Index/{expression}")]
    public IActionResult Index(string expression)
    {
        return View(new CalculatorData(expression, _smartCalculator.History!));
    }

    [HttpPost]
    [Route("Home/Calculate/{expression}/{x}")]
    public IActionResult Calculate(string expression, double x)
    {
        try
        {
            StringBuilder sb = new(expression);
            sb.Replace("x", x.ToString());
            _smartCalculator.CalculateExpression(sb);
            CalculatorData data = new CalculatorData(expression, _smartCalculator.History!, _smartCalculator.Answer ?? "", _smartCalculator.Status);
            return View("Index", data);
        }
        catch (Exception)
        {
            return View("Error");
        }
    }

    [HttpPost]
    [Route("/Home/BuildGraph/{expression}/{xMin}/{xMax}/{yMin}/{yMax}")]
    public IActionResult BuildGraph(string expression, double xMin, double xMax, double yMin, double yMax)
    {
        try
        { 
            if (xMin >= xMax || yMin >= yMax)
            {
                return View("Index", new CalculatorData(expression, _smartCalculator.History!, "", false));
            }
            _smartCalculator.GetCoordinates(xMin, xMax, new StringBuilder(expression));
            CalculatorData data = new CalculatorData(_smartCalculator.History!, _smartCalculator.CoordinateX, _smartCalculator.CoordinateY);
            data.CurrentExpression = expression;
            data.GraphSize = new Dictionary<string, double> { { "xMin", xMin }, { "xMax", xMax }, { "yMin", yMin }, { "yMax", yMax } };
            return View("Index", data);
        }
            catch (Exception)
            {
                return View("Error");
        }
    }

    [HttpGet]
    [Route("/Home/ClearHistory")]
    public IActionResult ClearHistory()
    {
        try
        {
            _smartCalculator.ClearHistory();
            return View("Index", new CalculatorData(_smartCalculator.History!, null));
        }
        catch (Exception)
        {
            return View("Error");
        }
    }

    public IActionResult Help()
    {
        return View();
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }
}


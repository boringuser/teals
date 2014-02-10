using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web.Helpers;
using System.Web.Mvc;
using MvcMovie.Models;

namespace MvcMovie.Controllers
{
    public class ReportController : Controller
    {
        private MovieDBContext db = new MovieDBContext();

        public ActionResult Index()
        {
            return View();
        }

        private ActionResult GetChart(IEnumerable<string> xValues, IEnumerable<int> yValues)
        {
            var chart = new Chart(width: 300, height: 200)
                .AddSeries(
                    chartType: "bar",
                    xValue: xValues,
                    yValues: yValues)
                .GetBytes("png");

            return File(chart, "image/bytes");
        }

        public ActionResult ChartByGenre()
        {
            var query = from m in db.Movies
                group m by m.Genre
                into grp
                select new
                {
                    Genre = grp.Key,
                    Count = grp.Select(m => m.Title).Distinct().Count()
                };

            var genres = new List<string>();
            var counts = new List<int>();

            foreach (var row in query.OrderBy(m => m.Genre))
            {
                genres.Add(row.Genre);
                counts.Add(row.Count);
            }

            return GetChart(genres, counts);
        }

        public ActionResult ChartByRating()
        {
            var query = from m in db.Movies
                        group m by m.Rating
                            into grp
                            select new
                            {
                                Rating = grp.Key,
                                Count = grp.Select(m => m.Title).Distinct().Count()
                            };

            var ratings = new List<string>();
            var counts = new List<int>();

            foreach (var row in query.OrderBy(m => m.Rating))
            {
                ratings.Add(row.Rating);
                counts.Add(row.Count);
            }

            return GetChart(ratings, counts);
        }
    }
}
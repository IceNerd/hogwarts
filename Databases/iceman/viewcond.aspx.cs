using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class viewcond : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Request.QueryString["rinkid"] == null)
        {
            Response.Redirect("Default.aspx");
        }
        else
        {
            SqlConnection conDB;
            SqlCommand cmdDB;
            SqlDataReader rdrDB;
            string strCMD;

            conDB = new SqlConnection(IceMan.Database.GetConnectionString("ConnectionString"));
            conDB.Open();

            cmdDB = new SqlCommand("SELECT MAX( conditionid ) FROM condition", conDB);
            strCMD = "SELECT airtemp, icetemp, stamp, empid, windspeed, weather, seapressure, dewpoint, cloudcover FROM condition WHERE conditionid=";
            strCMD += cmdDB.ExecuteScalar().ToString();

            cmdDB = new SqlCommand(strCMD, conDB);
            rdrDB = cmdDB.ExecuteReader();

            lblTitle.Text = "Current Conditions for " + Request.QueryString["rinkname"].ToString();
            if (rdrDB.Read())
            {
                lblAirTemp.Text = "Air Temp: " + rdrDB["airtemp"].ToString();
                lblIceTemp.Text = "Ice Temp: " + rdrDB["icetemp"].ToString();
                lblDateTime.Text = "Taken: " + rdrDB["stamp"].ToString();
                lblWindSpeed.Text = "Wind Speed: " + rdrDB["windspeed"].ToString();
                lblWeather.Text = "Weather: " + rdrDB["weather"].ToString();
                lblSeaPressure.Text = "Sea Pressure: " + rdrDB["seapressure"].ToString();
                lblDewPoint.Text = "Dew Point: " + rdrDB["dewpoint"].ToString();
                lblCloudCover.Text = "Cloud Cover: " + rdrDB["cloudcover"].ToString();
            }
            conDB.Close();
        }
    }
}

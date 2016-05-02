using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class addcond : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if( Request.QueryString["rinkid"] == null )
        {
            Response.Redirect("Default.aspx");
        }
        else
        {
            lblRinkTitle.Text = "Add Conditions to: " + Request.QueryString["rinkname"].ToString();
        }
    }

    protected void btnAddCond_Click(object sender, EventArgs e)
    {
            SqlConnection conDB;
            SqlCommand cmdDB;
            string strAddCondINTO;
            string strAddCondVALUES;
            strAddCondINTO = "INSERT INTO condition( airtemp, icetemp, rinkid, empid, stamp";
            strAddCondVALUES = " VALUES( ";
            strAddCondVALUES += txtAirTemp.Text.ToString();
            strAddCondVALUES += ", " + txtIceTemp.Text.ToString();
            strAddCondVALUES += ", " + Request.QueryString["rinkid"].ToString();
            strAddCondVALUES += ", " + ddlEmp.SelectedValue.ToString();
            strAddCondVALUES += ", '" + txtDate.Text.ToString() + " " + txtHour.Text.ToString() + ":" + txtMinute.Text.ToString() + " " + ddlAMPM.SelectedValue.ToString() + "'";

            if (ddlWindSpeed.SelectedValue.ToString() != "-1")
            {
                strAddCondINTO += ", windspeed";
                strAddCondVALUES += ", " + ddlWindSpeed.SelectedValue.ToString();
            }
            if (ddlWeather.SelectedValue.ToString() != "-1")
            {
                strAddCondINTO += ", weather";
                strAddCondVALUES += ", " + ddlWeather.SelectedValue.ToString();
            }
            if (txtSeaLvlPressure.Text.ToString() != "")
            {
                strAddCondINTO += ", seapressure";
                strAddCondVALUES += ", " + txtSeaLvlPressure.Text.ToString();
            }
            if (valDewPoint.IsValid && valDewPoint.Text.ToString() != "")
            {
                strAddCondINTO += ", dewpoint";
                strAddCondVALUES += ", " + txtDewPoint.Text.ToString();
            }
            if (ddlCloudCover.SelectedValue.ToString() != "-1")
            {
                strAddCondINTO += ", cloudcover";
                strAddCondVALUES += ", " + ddlCloudCover.SelectedValue.ToString();
            }
            strAddCondINTO += " )";
            strAddCondVALUES += " )";

            string strCMD;
            strCMD = strAddCondINTO + strAddCondVALUES;

            conDB = new SqlConnection(IceMan.Database.GetConnectionString("ConnectionString"));
            conDB.Open();

            cmdDB = new SqlCommand(strCMD, conDB);
            if (cmdDB.ExecuteNonQuery() == 0)
            {
                throw new Exception("Failed to insert new condition");
            }

            Response.Redirect("rinks.aspx");
    }
}

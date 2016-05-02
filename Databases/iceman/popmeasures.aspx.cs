using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class popmeasures : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        SqlConnection conDB;
        SqlCommand cmdDB;
        SqlDataReader rdrDB;

        conDB = new SqlConnection(IceMan.Database.GetConnectionString("ConnectionString"));
        conDB.Open();

        if (Request.QueryString["rinkid"] != null)
        {
            string strCMD;
            string strURL;
            strCMD = "SELECT MAX( icedepthid ) FROM icedepth WHERE rinkid=" + Request.QueryString["rinkid"].ToString();
            cmdDB = new SqlCommand(strCMD, conDB);
            strURL = "popmeasures.aspx?icedepthid=";
            strURL += cmdDB.ExecuteScalar().ToString();

            conDB.Close();
            Response.Redirect(strURL);
        }
        else if (Request.QueryString["icedepthid"] == null)
        {
            Response.Redirect("Default.aspx");
        }
        else 
        {
            string strLItem;
            string strGetMeas;
            strGetMeas = "SELECT height, sectionx, sectiony, subx, suby FROM measure, icedepth_measure WHERE measure.measureid = icedepth_measure.measureid AND icedepth_measure.icedepthid = ";
            strGetMeas += Request.QueryString["icedepthid"];

            cmdDB = new SqlCommand(strGetMeas, conDB);
            rdrDB = cmdDB.ExecuteReader();
            while(rdrDB.Read())
            {
                strLItem = rdrDB["height"] + "@(" + rdrDB["sectionx"] + ", " + rdrDB["sectiony"] + ") (" + rdrDB["subx"] + ", " + rdrDB["suby"] + ")";
                lstMeasures.Items.Add(strLItem);
            }
            rdrDB.Close();
        }

        conDB.Close();
    }
    protected void btnAddMeasure_Click(object sender, EventArgs e)
    {
        SqlConnection conDB;
        SqlCommand cmdDB;
        string strCMD;
        strCMD = "INSERT INTO measure( height, sectionx, sectiony, subx, suby ) VALUES( ";
        strCMD += txtHeight.Text.ToString();
        strCMD += ", " + txtSectX.Text.ToString();
        strCMD += ", " + txtSectY.Text.ToString();
        strCMD += ", " + txtSubX.Text.ToString();
        strCMD += ", " + txtSubY.Text.ToString();
        strCMD += " )";

        conDB = new SqlConnection(IceMan.Database.GetConnectionString("ConnectionString"));
        conDB.Open();
        cmdDB = new SqlCommand(strCMD, conDB);

        if (cmdDB.ExecuteNonQuery() == 0)
        {
            throw new Exception("Failed to insert measurement");
        }

        cmdDB = new SqlCommand("SELECT @@IDENTITY", conDB);
        strCMD = "INSERT INTO icedepth_measure( icedepthid, measureid ) VALUES( ";
        strCMD += Request.QueryString["icedepthid"].ToString();
        strCMD += ", " + cmdDB.ExecuteScalar().ToString() + " )";

        cmdDB = new SqlCommand(strCMD, conDB);
        if (cmdDB.ExecuteNonQuery() == 0)
        {
            throw new Exception("Failed to insert link of depth to measurement");
        }
        conDB.Close();

        strCMD = "popmeasures.aspx?icedepthid=" + Request.QueryString["icedepthid"].ToString();
        Response.Redirect(strCMD);
    }
}

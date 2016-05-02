using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class adddepth : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Request.QueryString["rinkid"] == null)
        {
            Response.Redirect("Default.aspx");
        }
        else
        {
            lblTitle.Text = "Log Depth for " + Request.QueryString["rinkname"].ToString();
        }
    }
    protected void btnAddDepth_Click(object sender, EventArgs e)
    {
        SqlConnection conDB;
        SqlCommand cmdDB;
        string strAddIceDepth;
        strAddIceDepth = "INSERT INTO icedepth( rinkid, empid, stamp ) VALUES( ";
        strAddIceDepth += Request.QueryString["rinkid"].ToString();
        strAddIceDepth += ", " + ddlEmp.SelectedValue.ToString();
        strAddIceDepth += ", '" + txtDate.Text.ToString() + " " + txtHour.Text.ToString() + ":" + txtMinute.Text.ToString() + " " + ddlAMPM.SelectedValue.ToString();
        strAddIceDepth += "' )";

        conDB = new SqlConnection(IceMan.Database.GetConnectionString("ConnectionString"));
        conDB.Open();

        cmdDB = new SqlCommand(strAddIceDepth, conDB);
        if (cmdDB.ExecuteNonQuery() == 0)
        {
            throw new Exception("Failed to insert new depth");
        }

        cmdDB = new SqlCommand("SELECT @@IDENTITY", conDB);

        string strURL;
        strURL = "popmeasures.aspx?icedepthid=" + cmdDB.ExecuteScalar().ToString();

        conDB.Close();
        Response.Redirect(strURL);
    }
}

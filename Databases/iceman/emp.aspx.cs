using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class addemp : System.Web.UI.Page
{

    protected void lstActiveEmp_SelectedIndexChanged(object sender, EventArgs e)
    {
        SqlConnection conDB;
        SqlCommand cmdDB;
        SqlDataReader rdrDB;

        conDB = new SqlConnection( IceMan.Database.GetConnectionString("ConnectionString") );
        conDB.Open();

        cmdDB = new SqlCommand( "SELECT fname, lname, active, addressid FROM emp WHERE empid=" + lstActiveEmp.SelectedValue, conDB );
        rdrDB = cmdDB.ExecuteReader();

        if (rdrDB.Read())
        {
            lblName.Text = rdrDB["fname"].ToString() + " " + rdrDB["lname"];
            if (rdrDB["active"].ToString() == "y")
            {
                lblActive.Text = "ACTIVE";
                lblActive.Style.Clear();
                lblActive.Style.Add( "text-decoration", "strong" );
                lblActive.Style.Add( "color", "#0000FF" );
            }
            else
            {
                lblActive.Text = "INACTIVE";
                lblActive.Style.Clear();
                lblActive.Style.Add("text-decoration", "strong");
                lblActive.Style.Add("color", "#000000");
                lblActive.Style.Add("background-color", "#FF0000");
            }
            cmdDB = new SqlCommand("SELECT address1, address2, city, state, zip FROM address WHERE addressid=" + rdrDB["addressid"], conDB);
            rdrDB.Close();

            rdrDB = cmdDB.ExecuteReader();
            if (rdrDB.Read())
            {
                lblAddress.Text = rdrDB["address1"].ToString();
                lblAddress2.Text = rdrDB["address2"].ToString();
                if (rdrDB["address2"].ToString() == "")
                {
                    lblAddress2.Style.Clear();
                    lblAddress2.Style.Add("display", "inline");
                }
                else
                {
                    lblAddress2.Style.Clear();
                    lblAddress2.Style.Add("display", "block");
                }
                lblCSZ.Text = rdrDB["city"] + ", " + rdrDB["state"] + ", " + rdrDB["zip"];
                rdrDB.Close();
            }
        }

        conDB.Close();
    }
}

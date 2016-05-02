using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class addrink : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void lstRinks_SelectedIndexChanged(object sender, EventArgs e)
    {
        SqlConnection conDB;
        SqlCommand cmdDB;
        SqlDataReader rdrDB;

        btnAddCond.Visible = true;
        btnAddDepth.Visible = true;
        btnViewCond.Visible = true;
        btnViewDepth.Visible = true;

        conDB = new SqlConnection(IceMan.Database.GetConnectionString("ConnectionString"));
        conDB.Open();

        cmdDB = new SqlCommand("SELECT name, typeofrink, addressid, height, width FROM rink WHERE rinkid=" + lstRinks.SelectedValue, conDB);
        rdrDB = cmdDB.ExecuteReader();

        if (rdrDB.Read())
        {
            lblName.Text = rdrDB["name"].ToString();
            lblDetail.Text = rdrDB["width"].ToString() + "ft X " + rdrDB["height"] + "ft";
            lblType.Text = "Slab Type: " + rdrDB["typeofrink"].ToString();

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
    protected void btnAddCond_Click(object sender, EventArgs e)
    {
        string strURL;
        strURL = "addcond.aspx?rinkid=" + lstRinks.SelectedValue.ToString() + "&rinkname=" + lstRinks.SelectedItem.Text.ToString();

        Response.Redirect(strURL);
    }
    protected void btnViewCond_Click(object sender, EventArgs e)
    {
        string strURL;
        strURL = "viewcond.aspx?rinkid=" + lstRinks.SelectedValue.ToString() + "&rinkname=" + lstRinks.SelectedItem.Text.ToString();

        Response.Redirect(strURL);
    }
    protected void btnAddDepth_Click(object sender, EventArgs e)
    {
        string strURL;
        strURL = "adddepth.aspx?rinkid=" + lstRinks.SelectedValue.ToString() + "&rinkname=" + lstRinks.SelectedItem.Text.ToString();

        Response.Redirect(strURL);
    }
    protected void btnViewDepth_Click(object sender, EventArgs e)
    {
        string strURL;
        strURL = "popmeasures.aspx?rinkid=" + lstRinks.SelectedValue.ToString() + "&rinkname=" + lstRinks.SelectedItem.Text.ToString();

        Response.Redirect(strURL);
    }
}

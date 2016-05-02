using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class addAddress : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btnAddAddress_Click(object sender, EventArgs e)
    {
        if (Page.IsValid)
        {
            SqlConnection conDB;
            SqlCommand cmdDB;
            string strAddRink;
            strAddRink = "INSERT INTO address( address1, ";
            if (txtAddress2.Text.ToString() != "")
            {
                strAddRink += "address2, ";
            }
            strAddRink += " city, state, zip ) VALUES( ";
            strAddRink += "'" + txtAddress1.Text.ToString() + "', ";
            if (txtAddress2.Text.ToString() != "")
            {
                strAddRink += "'" + txtAddress2.Text.ToString() + "', ";
            }
            strAddRink += "'" + txtCity.Text.ToString() + "', ";
            strAddRink += "'" + ddlState.SelectedValue.ToString() + "', ";
            strAddRink += "'" + txtZip.Text.ToString() + "')";

            conDB = new SqlConnection(IceMan.Database.GetConnectionString("ConnectionString"));
            conDB.Open();

            cmdDB = new SqlCommand(strAddRink, conDB);
            if (cmdDB.ExecuteNonQuery() == 0)
            {
                throw new Exception("Failed to insert new address");
            }

            Server.Transfer("Default.aspx");
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class addemp : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btnAddEmp_Click(object sender, EventArgs e)
    {
        if (Page.IsValid)
        {
            SqlConnection conDB;
            SqlCommand cmdDB;
            string strAddRink;
                strAddRink = "INSERT INTO emp( fname, lname, addressid, active ) VALUES( '";
                strAddRink += txtFName.Text.ToString() + "', '";
                strAddRink += txtLName.Text.ToString() + "', ";
                strAddRink += ddlAddress.SelectedValue.ToString() + ", 'n' )";

            conDB = new SqlConnection(IceMan.Database.GetConnectionString("ConnectionString"));
            conDB.Open();

            cmdDB = new SqlCommand(strAddRink, conDB);
            if (cmdDB.ExecuteNonQuery() == 0)
            {
                throw new Exception("Failed to insert new employee");
            }

            Response.Redirect("Default.aspx");
        }
    }
}

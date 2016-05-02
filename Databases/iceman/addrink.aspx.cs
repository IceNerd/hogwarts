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
    protected void btnAdd_Click(object sender, EventArgs e)
    {
        if (Page.IsValid)
        {
            SqlConnection conDB;
            SqlCommand cmdDB;
            string strAddRink;
                strAddRink = "INSERT INTO rink( name, typeofrink, addressid, height, width ) VALUES( '";
                strAddRink += txtName.Text.ToString() + "', '";
                strAddRink += DDLType.SelectedItem.Text.ToString() + "', ";
                strAddRink += DDLAddress.SelectedValue.ToString() + ", ";
                strAddRink += txtHeight.Text.ToString() + ", ";
                strAddRink += txtWidth.Text.ToString() + ")";

            conDB = new SqlConnection( IceMan.Database.GetConnectionString("ConnectionString") );
            conDB.Open();

            cmdDB = new SqlCommand( strAddRink, conDB );
            if( cmdDB.ExecuteNonQuery() == 0 )
            {
                throw new Exception( "Failed to insert new rink" );
            }

            Response.Redirect("Default.aspx") ;
        }
    }
}

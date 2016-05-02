using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Data.SqlClient;

public partial class _Default : System.Web.UI.Page 
{
    protected void Page_Load(object sender, EventArgs e)
    {
    }
    protected void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
        SqlConnection con_WhizzGet;

        con_WhizzGet = new SqlConnection(@"Data Source=ZENITRAM\WHIZZBANG;Initial Catalog=moviedb;User ID=zen;Password=test;Pooling=False");
        con_WhizzGet.Open();

        //Immediate Data
        SqlCommand cmd_Whizz;
        SqlDataReader dtr_Whizz;
        String ratingcmd;
        cmd_Whizz = new SqlCommand( "select ratingid, title, plotdescription, releaseyear, runningtime from movie where movieid = '" + movie_list.SelectedValue.ToString() + "'", con_WhizzGet );
        dtr_Whizz = cmd_Whizz.ExecuteReader();
        if( dtr_Whizz.Read() )
        {
            Session.RemoveAll();
            movie_title.Text = dtr_Whizz["title"].ToString();
            Session.Add("MovieTitle", movie_title.Text);
            Session.Add("MovieID", movie_list.SelectedValue);
            movie_desc.Text = dtr_Whizz["plotdescription"].ToString();
            movie_rlsyear.Text = "Release Year:   " + dtr_Whizz["releaseyear"].ToString();
            movie_rntime.Text = "Running Time:   " + dtr_Whizz["runningtime"].ToString() + " minutes";
            //get the rating
            ratingcmd = "select name from rating where ratingid = '" + dtr_Whizz["ratingid"].ToString() + "'";
            dtr_Whizz.Close();
            SqlCommand ncmd_Whizz;
            SqlDataReader ndtr_Whizz;
            ncmd_Whizz = new SqlCommand(ratingcmd, con_WhizzGet);
            ndtr_Whizz = ncmd_Whizz.ExecuteReader();
            if (ndtr_Whizz.Read())
            {
                movie_rating.Text = "Rated: " + ndtr_Whizz["name"].ToString();
            }
            ndtr_Whizz.Close();
        }
        dtr_Whizz.Close();

        //Retrieve Production Company List
        SqlDataAdapter ada_PC;
        DataSet ds_PC;
        ada_PC = new SqlDataAdapter("select company.name from company, movie_production where (movie_production.companyid = company.companyid) AND (movie_production.movieid = '" + movie_list.SelectedValue.ToString() + "')", con_WhizzGet);
        ds_PC = new DataSet();
        ada_PC.Fill(ds_PC, "company");
        movie_production.DataSource = ds_PC;
        movie_production.DataBind();

        //Retrieve Studio Company List
        SqlDataAdapter ada_SC;
        DataSet ds_SC;
        ada_SC = new SqlDataAdapter("select company.name from company, movie_studio where (movie_studio.companyid = company.companyid) AND (movie_studio.movieid = '" + movie_list.SelectedValue.ToString() + "')", con_WhizzGet);
        ds_SC = new DataSet();
        ada_SC.Fill(ds_SC, "company");
        movie_studio.DataSource = ds_SC;
        movie_studio.DataBind();

        //Retrieve Director List
        SqlDataAdapter ada_D;
        DataSet ds_D;
        ada_D = new SqlDataAdapter("select person.firstname, person.lastname, movie_director.detail_role from person, movie_director where (movie_director.personid = person.personid) AND (movie_director.movieid = '" + movie_list.SelectedValue.ToString() + "')", con_WhizzGet);
        ds_D = new DataSet();
        ada_D.Fill(ds_D, "person");
        movie_director.DataSource = ds_D;
        movie_director.DataBind();

        //Retrieve Writer List
        SqlDataAdapter ada_W;
        DataSet ds_W;
        ada_W = new SqlDataAdapter("select person.firstname, person.lastname, movie_writer.detail_role from person, movie_writer where (movie_writer.personid = person.personid) AND (movie_writer.movieid = '" + movie_list.SelectedValue.ToString() + "')", con_WhizzGet);
        ds_W = new DataSet();
        ada_W.Fill(ds_W, "person");
        movie_writers.DataSource = ds_W;
        movie_writers.DataBind();

        //Retrieve Producer List
        SqlDataAdapter ada_PP;
        DataSet ds_PP;
        ada_PP = new SqlDataAdapter("select person.firstname, person.lastname, movie_producer.detail_role from person, movie_producer where (movie_producer.personid = person.personid) AND (movie_producer.movieid = '" + movie_list.SelectedValue.ToString() + "')", con_WhizzGet);
        ds_PP = new DataSet();
        ada_PP.Fill(ds_PP, "person");
        movie_producers.DataSource = ds_PP;
        movie_producers.DataBind();

        //Retrieve Actor List
        SqlDataAdapter ada_A;
        DataSet ds_A;
        ada_A = new SqlDataAdapter("select person.firstname, person.lastname, movie_actor.detail_role from person, movie_actor where (movie_actor.personid = person.personid) AND (movie_actor.movieid = '" + movie_list.SelectedValue.ToString() + "')", con_WhizzGet);
        ds_A = new DataSet();
        ada_A.Fill(ds_A, "person");
        movie_actors.DataSource = ds_A;
        movie_actors.DataBind();

        //Retrieve Genre List
        SqlDataAdapter ada_G;
        DataSet ds_G;
        ada_G = new SqlDataAdapter("select genre.name from genre, movie_genre where (movie_genre.genreid = genre.genreid) AND (movie_genre.movieid = '" + movie_list.SelectedValue.ToString() + "')", con_WhizzGet);
        ds_G = new DataSet();
        ada_G.Fill(ds_G, "genre");
        movie_genre.DataSource = ds_G;
        movie_genre.DataBind();


        con_WhizzGet.Close();
    }
    protected void DataList1_SelectedIndexChanged(object sender, EventArgs e)
    {

    }

    protected void Edit_PC_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("CompanyType", "production");
            Response.Redirect("AddCompany.aspx");
        }
    }

    protected void Delete_PC_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("CompanyType", "production");
            Response.Redirect("RemoveCompany.aspx");
        }
    }

    protected void Edit_STUD_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("CompanyType", "studio");
            Response.Redirect("AddCompany.aspx");
        }
    }

    protected void Delete_STUD_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("CompanyType", "studio");
            Response.Redirect("RemoveCompany.aspx");
        }
    }

    protected void Edit_DIRS_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("PersonType", "director");
            Response.Redirect("AddPerson.aspx");
        }
    }

    protected void Delete_DIRS_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("PersonType", "director");
            Response.Redirect("RemovePerson.aspx");
        }
    }

    protected void Edit_WR_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("PersonType", "writer");
            Response.Redirect("AddPerson.aspx");
        }
    }

    protected void Delete_WR_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("PersonType", "writer");
            Response.Redirect("RemovePerson.aspx");
        }
    }

    protected void Edit_PROD_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("PersonType", "producer");
            Response.Redirect("AddPerson.aspx");
        }
    }

    protected void Delete_PROD_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("PersonType", "producer");
            Response.Redirect("RemovePerson.aspx");
        }
    }

    protected void Edit_ACT_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("PersonType", "actor");
            Response.Redirect("AddPerson.aspx");
        }
    }

    protected void Delete_ACT_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Session.Add("PersonType", "actor");
            Response.Redirect("RemovePerson.aspx");
        }
    }

    protected void Edit_GEN_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Response.Redirect("AddGenre.aspx");
        }
    }

    protected void Delete_GEN_Command(object sender, DataListCommandEventArgs e)
    {
        if (movie_list.SelectedIndex != -1)
        {
            Response.Redirect("RemoveGenre.aspx");
        }
    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        
    }
    protected void Button3_Click(object sender, EventArgs e)
    {

    }
    protected void Button1_Click1(object sender, EventArgs e)
    {
        Response.Redirect("AddMovie.aspx");
    }
}

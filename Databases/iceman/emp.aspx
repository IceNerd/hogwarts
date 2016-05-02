<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="emp.aspx.cs" Inherits="addemp" %>

<asp:Content ID="Content1" runat="server" contentplaceholderid="navContent">
    <li><a href="addemp.aspx">Add Employee</a></li>
</asp:Content>

<asp:Content ID="Content2" runat="server" contentplaceholderid="mainContent">

    <%--Data Sources--%>
    <asp:SqlDataSource ID="DSEmp" runat="server" 
    ConnectionString="<%$ ConnectionStrings:ConnectionString %>" 
    SelectCommand="SELECT empid, lname + ', ' + fname AS name FROM emp ORDER BY lname">
    </asp:SqlDataSource>
    
    <%--Page Content--%>
    <div style="float: left; margin: 5px 5px 5px 5px;">
        <asp:ListBox ID="lstActiveEmp" runat="server" DataSourceID="DSEmp" 
        DataTextField="name" DataValueField="empid" Height="160px" Width="140px" 
            AutoPostBack="True" onselectedindexchanged="lstActiveEmp_SelectedIndexChanged">
        </asp:ListBox>
    </div>
    
    <div id="empdiv">
        <div style="float: right;">
            <asp:Label ID="lblActive" runat="server" Text=""></asp:Label>
        </div>

        <asp:Label ID="lblName" runat="server" Text=""></asp:Label>
        <br />
        <asp:Label ID="lblAddress" runat="server" Text=""></asp:Label>
        <br />
        <asp:Label ID="lblAddress2" runat="server"></asp:Label>
        <asp:Label ID="lblCSZ" runat="server" Text=""></asp:Label>
        <br />
        <br />

    </div>
   
</asp:Content>



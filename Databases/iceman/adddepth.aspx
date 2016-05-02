<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="adddepth.aspx.cs" Inherits="adddepth" %>

<asp:Content ID="Content1" ContentPlaceHolderID="mainContent" Runat="Server">
    <asp:Label ID="lblTitle" runat="server" Font-Bold="True"></asp:Label>
    <br />
    Performed by:
    <asp:DropDownList ID="ddlEmp" runat="server" DataSourceID="dsActiveEmp" 
        DataTextField="name" DataValueField="empid" Height="22px" Width="200px">
    </asp:DropDownList>
    <asp:SqlDataSource ID="dsActiveEmp" runat="server" 
        ConnectionString="<%$ ConnectionStrings:ConnectionString %>" 
        SelectCommand="SELECT empid, lname + ', ' + fname AS name FROM emp WHERE active='y'">
    </asp:SqlDataSource>
    <br />
    Time:
    <asp:TextBox ID="txtHour" runat="server" Width="50px" MaxLength="2"></asp:TextBox>
    <asp:TextBox ID="txtMinute" runat="server" Width="50px" MaxLength="2" 
        Height="22px"></asp:TextBox>
    <asp:DropDownList ID="ddlAMPM" runat="server" Height="22px" Width="50px">
        <asp:ListItem>AM</asp:ListItem>
        <asp:ListItem Selected="True">PM</asp:ListItem>
    </asp:DropDownList>
    <br />
    Date:
    <asp:TextBox ID="txtDate" runat="server">
    </asp:TextBox>
    <br />
    <br />
    <asp:Button ID="btnAddDepth" runat="server" onclick="btnAddDepth_Click" 
        Text="Continue" />
</asp:Content>


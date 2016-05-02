<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="addemp.aspx.cs" Inherits="addemp" %>

<asp:Content ID="Content1" ContentPlaceHolderID="navContent" Runat="Server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="mainContent" Runat="Server">
    <p>
        First Name:<asp:TextBox ID="txtFName" runat="server" MaxLength="50" 
            Width="175px"></asp:TextBox>
        <asp:RequiredFieldValidator ID="valFName" runat="server" 
            ControlToValidate="txtFName" ErrorMessage="*"></asp:RequiredFieldValidator>
    </p>
    <p>
        Last Name:<asp:TextBox ID="txtLName" runat="server" MaxLength="50" 
            Width="175px"></asp:TextBox>
        <asp:RequiredFieldValidator ID="valLName" runat="server" 
            ControlToValidate="txtLName" ErrorMessage="*"></asp:RequiredFieldValidator>
    </p>
    <p>
        <asp:DropDownList ID="ddlAddress" runat="server" DataSourceID="dsAddress" 
            DataTextField="addy" DataValueField="addressid" Height="22px" Width="500px">
        </asp:DropDownList>
        <asp:SqlDataSource ID="dsAddress" runat="server" 
            ConnectionString="<%$ ConnectionStrings:ConnectionString %>" SelectCommand="SELECT addressid,
address1 + ', ' + COALESCE( address2, '' ) + ', ' + city + ' ' + state + ' ' + zip as addy
FROM address"></asp:SqlDataSource>
        <asp:Button ID="btnAddEmp" runat="server" onclick="btnAddEmp_Click" 
            Text="Add Employee" />
    </p>
</asp:Content>


<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="addrink.aspx.cs" Inherits="addrink" %>

<asp:Content ID="Content1" ContentPlaceHolderID="navContent" Runat="Server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="mainContent" Runat="Server">

    <p>
        Name:&nbsp;
        <asp:TextBox ID="txtName" runat="server" MaxLength="50" Width="250px"></asp:TextBox>
        <asp:RequiredFieldValidator ID="valName" runat="server" ErrorMessage="*" 
            ControlToValidate="txtName"></asp:RequiredFieldValidator>
    </p>
    <p>
        Width:&nbsp;
        <asp:TextBox ID="txtWidth" runat="server" MaxLength="8" Width="75px"></asp:TextBox>ft
        <asp:CompareValidator ID="txtWidthValidator" ControlToValidate="txtWidth" runat="server" ErrorMessage="Invalid! ex: 123.45" Operator="DataTypeCheck" Type="Currency"></asp:CompareValidator>
    </p>
    <p>
        Height:&nbsp;
        <asp:TextBox ID="txtHeight" runat="server" MaxLength="8" Width="75px"></asp:TextBox>ft
        <asp:CompareValidator ID="txtHeightValidator" ControlToValidate="txtHeight" runat="server" ErrorMessage="Invalid!  ex: 123.45" Operator="DataTypeCheck" Type="Currency"></asp:CompareValidator>
    </p>
    <p>
        Type:&nbsp;
        <asp:DropDownList ID="DDLType" runat="server" Height="22px" Width="120px">
            <asp:ListItem>Cement</asp:ListItem>
            <asp:ListItem>Sand</asp:ListItem>
        </asp:DropDownList>
    </p>
    <p>
        Address:
        <asp:DropDownList ID="DDLAddress" runat="server" DataSourceID="DSAddresses" 
            DataTextField="addy" DataValueField="addressid" Width="500px">
        </asp:DropDownList>
        <asp:SqlDataSource ID="DSAddresses" runat="server" 
            ConnectionString="<%$ ConnectionStrings:ConnectionString %>" SelectCommand="SELECT addressid,
address1 + ', ' + COALESCE( address2, '' ) + ', ' + city + ' ' + state + ' ' + zip as addy
FROM address"></asp:SqlDataSource>
    </p>
    <p>
        <asp:Button ID="btnAdd" runat="server" onclick="btnAdd_Click" Text="Add Rink" />
    </p>

</asp:Content>


<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="addaddress.aspx.cs" Inherits="addAddress" %>

<asp:Content ID="Content1" ContentPlaceHolderID="navContent" Runat="Server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="mainContent" Runat="Server">
    
    <p>
        <asp:TextBox ID="txtAddress1" runat="server" Width="300px"></asp:TextBox>
        <asp:RequiredFieldValidator ID="valAddress1" runat="server" 
            ControlToValidate="txtAddress1" ErrorMessage="*"></asp:RequiredFieldValidator>
    </p>
    <p>
        <asp:TextBox ID="txtAddress2" runat="server" Width="300px"></asp:TextBox>
    </p>
    <p>
        City:
        <asp:TextBox ID="txtCity" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="valCity" runat="server" 
            ControlToValidate="txtCity" ErrorMessage="*"></asp:RequiredFieldValidator>
&nbsp;State:
        <asp:DropDownList ID="ddlState" runat="server">
            <asp:ListItem Value="AL">Alabama</asp:ListItem>
            <asp:ListItem Value="AK">Alaska</asp:ListItem>
            <asp:ListItem Value="AZ">Arizona</asp:ListItem>
            <asp:ListItem Value="AR">Arkansas</asp:ListItem>
            <asp:ListItem Value="CA">California</asp:ListItem>
            <asp:ListItem Value="CO">Colorado</asp:ListItem>
            <asp:ListItem Value="CT">Connecticut</asp:ListItem>
            <asp:ListItem Value="DC">District of Columbia</asp:ListItem>
            <asp:ListItem Value="DE">Delaware</asp:ListItem>
            <asp:ListItem Value="FL">Florida</asp:ListItem>
            <asp:ListItem Value="GA">Georgia</asp:ListItem>
            <asp:ListItem Value="HI">Hawaii</asp:ListItem>
            <asp:ListItem Value="ID">Idaho</asp:ListItem>
            <asp:ListItem Value="IL">Illinois</asp:ListItem>
            <asp:ListItem Value="IN">Indiana</asp:ListItem>
            <asp:ListItem Value="IA">Iowa</asp:ListItem>
            <asp:ListItem Value="KS">Kansas</asp:ListItem>
            <asp:ListItem Value="KY">Kentucky</asp:ListItem>
            <asp:ListItem Value="LA">Louisiana</asp:ListItem>
            <asp:ListItem Value="ME">Maine</asp:ListItem>
            <asp:ListItem Value="MD">Maryland</asp:ListItem>
            <asp:ListItem Value="MA">Massachusetts</asp:ListItem>
            <asp:ListItem Value="MI">Michigan</asp:ListItem>
            <asp:ListItem Value="MN">Minnesota</asp:ListItem>
            <asp:ListItem Value="MS">Mississippi</asp:ListItem>
            <asp:ListItem Value="MO">Missouri</asp:ListItem>
            <asp:ListItem Value="MT">Montana</asp:ListItem>
            <asp:ListItem Value="NE">Nebraska</asp:ListItem>
            <asp:ListItem Value="NV">Nevada</asp:ListItem>
            <asp:ListItem Value="NH">New Hampshire</asp:ListItem>
            <asp:ListItem Value="NJ">New Jersey</asp:ListItem>
            <asp:ListItem Value="NM">New Mexico</asp:ListItem>
            <asp:ListItem Value="NY">New York</asp:ListItem>
            <asp:ListItem Value="NC">North Carolina</asp:ListItem>
            <asp:ListItem Value="ND">North Dakota</asp:ListItem>
            <asp:ListItem Value="OH">Ohio</asp:ListItem>
            <asp:ListItem Value="OK">Oklahoma</asp:ListItem>
            <asp:ListItem Value="OR">Oregon</asp:ListItem>
            <asp:ListItem Value="PA">Pennsylvania</asp:ListItem>
            <asp:ListItem Value="RI">Rhode Island</asp:ListItem>
            <asp:ListItem Value="SC">South Carolina</asp:ListItem>
            <asp:ListItem Value="SD">South Dakota</asp:ListItem>
            <asp:ListItem Value="TN">Tennessee</asp:ListItem>
            <asp:ListItem Value="TX">Texas</asp:ListItem>
            <asp:ListItem Value="UT">Utah</asp:ListItem>
            <asp:ListItem Value="VT">Vermont</asp:ListItem>
            <asp:ListItem Value="VA">Virginia</asp:ListItem>
            <asp:ListItem Value="WA">Washington</asp:ListItem>
            <asp:ListItem Value="WV">West Virginia</asp:ListItem>
            <asp:ListItem Value="WI">Wisconsin</asp:ListItem>
            <asp:ListItem Value="WY">Wyoming</asp:ListItem>
        </asp:DropDownList>
&nbsp; Zip:
        <asp:TextBox ID="txtZip" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="valZip" runat="server" 
            ControlToValidate="txtZip" ErrorMessage="*"></asp:RequiredFieldValidator>
    </p>
    <p>
        <asp:Button ID="btnAddAddress" runat="server" Text="Add Address" 
            onclick="btnAddAddress_Click" />
    </p>
    
</asp:Content>


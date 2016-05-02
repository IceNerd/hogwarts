<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="rinks.aspx.cs" Inherits="addrink" %>

<asp:Content ID="Content1" ContentPlaceHolderID="navContent" Runat="Server">
    <li><a href="addrink.aspx">Add Rink</a></li>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="mainContent" Runat="Server">

    <%--Data Sources--%>
    <asp:SqlDataSource ID="DSRinks" runat="server" 
    ConnectionString="<%$ ConnectionStrings:ConnectionString %>" 
    SelectCommand="SELECT rinkid, name FROM rink">
    </asp:SqlDataSource>
    
    <%--Page Content--%>
    <div style="float: left; margin: 5px 5px 5px 5px;">
        <asp:ListBox ID="lstRinks" runat="server" DataSourceID="DSRinks" 
        DataTextField="name" DataValueField="rinkid" Height="160px" Width="140px" 
            AutoPostBack="True" onselectedindexchanged="lstRinks_SelectedIndexChanged">
        </asp:ListBox>
    </div>
    
    <div id="commondiv">
        <asp:Label ID="lblName" runat="server"></asp:Label>
        <br />
        <asp:Label ID="lblDetail" runat="server"></asp:Label>
        <br />
        <asp:Label ID="lblType" runat="server"></asp:Label>
        <br />
        <br />
        <asp:Label ID="lblAddress" runat="server"></asp:Label>
        <br />
        <asp:Label ID="lblAddress2" runat="server"></asp:Label>
        <asp:Label ID="lblCSZ" runat="server"></asp:Label>
        <br />
        <br />
        <asp:Button ID="btnViewCond" runat="server" Text="View Conditions" 
            Width="130px" Visible="False" onclick="btnViewCond_Click" />
        <asp:Button ID="btnViewDepth" runat="server" Text="View Ice Depth" 
            Width="130px" Visible="False" onclick="btnViewDepth_Click" />
        <br />
        <asp:Button ID="btnAddCond" runat="server" Text="Log Conditions" Width="130px" 
            Visible="False" onclick="btnAddCond_Click" />
        <asp:Button ID="btnAddDepth" runat="server" Text="Log Ice Depth" Width="130px" 
            Visible="False" onclick="btnAddDepth_Click" />
    </div>

</asp:Content>


<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="popmeasures.aspx.cs" Inherits="popmeasures" %>

<asp:Content ID="Content1" ContentPlaceHolderID="navContent" Runat="Server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="mainContent" Runat="Server">
    <asp:ImageMap 
        ID="mapRink" runat="server" 
        style="float: left"
        ImageUrl="~/hockeyrink85x100.png">
    </asp:ImageMap>

    <div style="margin-left: 290px; height: 600px">
        <asp:ListBox ID="lstMeasures" runat="server" Height="150px" Width="150px">
        </asp:ListBox>
        <br />
        <br />
        <asp:TextBox ID="txtSectX" runat="server" Width="75px"></asp:TextBox>
        <asp:TextBox ID="txtSectY" runat="server" Width="75px"></asp:TextBox>
        <br />
        <asp:TextBox ID="txtSubX" runat="server" Width="75px"></asp:TextBox>
        <asp:TextBox ID="txtSubY" runat="server" Width="75px"></asp:TextBox>
        <br />
        <br />
        Height:
        <asp:TextBox ID="txtHeight" runat="server"></asp:TextBox>
        <br />
        <asp:Button ID="btnAddMeasure" runat="server" onclick="btnAddMeasure_Click" 
            Text="Add Measurement" />
    </div>
</asp:Content>


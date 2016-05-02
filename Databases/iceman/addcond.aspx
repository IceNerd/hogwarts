<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="addcond.aspx.cs" Inherits="addcond" %>

<asp:Content ID="Content1" ContentPlaceHolderID="navContent" Runat="Server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="mainContent" Runat="Server">
    <asp:SqlDataSource ID="dsEmp" runat="server" 
        ConnectionString="<%$ ConnectionStrings:ConnectionString %>" 
        SelectCommand="SELECT empid, lname + ', ' + fname AS name FROM emp ORDER BY lname">
    </asp:SqlDataSource>
    <p>
    <asp:Label ID="lblRinkTitle" runat="server"></asp:Label>
    <br />
    Employee:<asp:DropDownList ID="ddlEmp" runat="server" DataSourceID="dsEmp" 
        DataTextField="name" DataValueField="empid" Height="22px" Width="200px">
    </asp:DropDownList>
    <br />
    Air Temperature:<asp:TextBox ID="txtAirTemp" runat="server" Width="64px" 
        MaxLength="5"></asp:TextBox>Farenheit
        <asp:RequiredFieldValidator ID="reqAirTemp" runat="server" ControlToValidate="txtAirTemp" ErrorMessage="*"></asp:RequiredFieldValidator>
&nbsp;<asp:CompareValidator ID="valAirTemp" runat="server" ControlToValidate="txtAirTemp" ErrorMessage="invalid input(ex: 34.5)" Operator="DataTypeCheck" Type="Currency"></asp:CompareValidator>
    <br />
    Ice Temperature:<asp:TextBox ID="txtIceTemp" runat="server" Width="64px" 
        MaxLength="5"></asp:TextBox>Farenheit<asp:RequiredFieldValidator ID="reqIceTemp" runat="server" ControlToValidate="txtIceTemp" ErrorMessage="*"></asp:RequiredFieldValidator>
&nbsp;<asp:CompareValidator ID="valIceTemp" runat="server" ControlToValidate="txtIceTemp" ErrorMessage="invalid input (ex: 21.6)" Operator="DataTypeCheck" Type="Currency"></asp:CompareValidator>
    <br />
    Wind Speed:<asp:DropDownList ID="ddlWindSpeed" runat="server" Height="22px" 
        Width="200px">
        <asp:ListItem Selected="True" Value="-1">No Data</asp:ListItem>
        <asp:ListItem Value="1">Calm</asp:ListItem>
        <asp:ListItem Value="2">5 Knots</asp:ListItem>
        <asp:ListItem Value="3">10 Knots</asp:ListItem>
        <asp:ListItem Value="4">15 Knots</asp:ListItem>
        <asp:ListItem Value="5">20 Knots</asp:ListItem>
        <asp:ListItem Value="6">50 Knots</asp:ListItem>
        <asp:ListItem Value="7">65 Knots</asp:ListItem>
    </asp:DropDownList>
    <br />
    Weather:<asp:DropDownList ID="ddlWeather" runat="server" Height="22px" 
        Width="200px">
        <asp:ListItem Selected="True" Value="-1">No Data</asp:ListItem>
        <asp:ListItem Value="1">Light Rain</asp:ListItem>
        <asp:ListItem Value="2">Moderate Rain</asp:ListItem>
        <asp:ListItem Value="3">Heavy Rain</asp:ListItem>
        <asp:ListItem Value="4">Light Shower</asp:ListItem>
        <asp:ListItem Value="5">Moderate Shower</asp:ListItem>
        <asp:ListItem Value="13">Light Drizzle</asp:ListItem>
        <asp:ListItem Value="14">Moderate Drizzle</asp:ListItem>
        <asp:ListItem Value="15">Heavy Drizzle</asp:ListItem>
        <asp:ListItem Value="8">Light Snow</asp:ListItem>
        <asp:ListItem Value="9">Moderate Snow</asp:ListItem>
        <asp:ListItem Value="10">Heavy Snow</asp:ListItem>
        <asp:ListItem Value="11">Light Snow Shower</asp:ListItem>
        <asp:ListItem Value="12">Moderate Snow Shower</asp:ListItem>
        <asp:ListItem Value="16">Light Freezing Rain</asp:ListItem>
        <asp:ListItem Value="17">Moderate Freezing Rain</asp:ListItem>
        <asp:ListItem Value="6">Thunderstorm</asp:ListItem>
        <asp:ListItem Value="7">Heavy Thunderstorm</asp:ListItem>
        <asp:ListItem Value="18">Haze</asp:ListItem>
        <asp:ListItem Value="19">Ice Crystals</asp:ListItem>
        <asp:ListItem Value="20">Fog</asp:ListItem>
    </asp:DropDownList>
    <br />
    Sea Level Pressure:<asp:TextBox ID="txtSeaLvlPressure" runat="server" 
        Height="22px" Width="64px" MaxLength="5"></asp:TextBox>millibars
    <asp:CompareValidator ID="valSeaLevelPressure" runat="server" ControlToValidate="txtSeaLvlPressure" ErrorMessage="Invalid" Operator="DataTypeCheck" Type="Currency"></asp:CompareValidator>
    <br />
    Dew Point:<asp:TextBox ID="txtDewPoint" runat="server" Width="64px" 
        MaxLength="5"></asp:TextBox>Farenheit
    <asp:CompareValidator ID="valDewPoint" runat="server" ControlToValidate="txtDewPoint" ErrorMessage="Invalid" Operator="DataTypeCheck" Type="Currency"></asp:CompareValidator>
    <br />
    Cloud Cover:<asp:DropDownList ID="ddlCloudCover" runat="server" Height="22px" 
        Width="200px">
        <asp:ListItem Value="0">0% - Clear Skies</asp:ListItem>
        <asp:ListItem Value="1">25% - Scattered Clouds</asp:ListItem>
        <asp:ListItem Value="2">75% - Broken Clouds</asp:ListItem>
        <asp:ListItem Value="3">100% - Overcast</asp:ListItem>
        <asp:ListItem Value="4">Vision Obscured</asp:ListItem>
        <asp:ListItem Selected="True" Value="5">No Data</asp:ListItem>
    </asp:DropDownList>
    <br />
    Time
    <asp:TextBox ID="txtHour" runat="server" Width="50px" MaxLength="2"></asp:TextBox>:
    <asp:TextBox ID="txtMinute" runat="server" Width="50px" MaxLength="2"></asp:TextBox>
    <asp:DropDownList ID="ddlAMPM" runat="server" Height="22px" Width="50px">
        <asp:ListItem>AM</asp:ListItem>
        <asp:ListItem Selected="True">PM</asp:ListItem>
    </asp:DropDownList>
    <asp:RequiredFieldValidator ID="reqHour" runat="server" ControlToValidate="txtHour" ErrorMessage="require Hour"></asp:RequiredFieldValidator>&nbsp;
    <asp:RequiredFieldValidator ID="reqMinute" runat="server" ControlToValidate="txtMinute" ErrorMessage="require Minute"></asp:RequiredFieldValidator>&nbsp;
    <asp:RangeValidator ID="valHour" runat="server" ControlToValidate="txtHour" ErrorMessage="invalid hour" Type="Integer" MaximumValue="12" MinimumValue="1"></asp:RangeValidator>&nbsp;
    <asp:RangeValidator ID="valMinute" runat="server" ControlToValidate="txtMinute" ErrorMessage="invalid minute" Type="Integer" MaximumValue="60" MinimumValue="1"></asp:RangeValidator>
    <br />
    Date:
    <asp:TextBox ID="txtDate" runat="server">
    </asp:TextBox><asp:RequiredFieldValidator ID="reqDate" runat="server" ControlToValidate="txtDate" ErrorMessage="*"></asp:RequiredFieldValidator>
    <br />
    <asp:Button ID="btnAddCond" runat="server" onclick="btnAddCond_Click" Text="Add" />
    <br />
    </p>
</asp:Content>


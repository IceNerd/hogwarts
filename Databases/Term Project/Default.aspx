<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>Untitled Page</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <span style="font-size: 14pt; font-family: Arial">
            <span></span><span style="color: black; background-color: white"><strong><span style="text-decoration: underline">
                Movie Collection Manager</span></strong><br />
                <br />
            </span>
            <asp:ListBox ID="movie_list" runat="server" Height="500px" Width="225px" DataSourceID="SqlDataSource1" DataTextField="title" DataValueField="movieid" OnSelectedIndexChanged="ListBox1_SelectedIndexChanged" AutoPostBack="True"></asp:ListBox><br />
            <asp:Button ID="Button1" runat="server" OnClick="Button1_Click1" Text="Add Movie" /><br />
            <div style="z-index: 101; left: 282px; width: 500px; position: absolute; top: 20px;
                height: 700px; text-align: left; font-weight: bold;">
                <asp:Image ID="movie_image" runat="server" Height="175px" Width="150px" /><br />
                <br />
                <asp:Label ID="movie_title" runat="server" Font-Bold="True" Font-Size="X-Large" Font-Underline="True" Width="50px" Font-Names="Arial"></asp:Label><br />
                <asp:Label ID="movie_desc" runat="server" Font-Names="Arial" Font-Size="10pt"></asp:Label><br />
                <br />
                <span style="font-size: 10pt">
                    <asp:Label ID="movie_rating" runat="server" Font-Names="Arial" Font-Size="10pt"></asp:Label><br />
                </span>
                <br />
                <span style="font-size: 10pt">
                    <asp:Label ID="movie_rntime" runat="server" Font-Names="Arial" Font-Size="10pt"></asp:Label><br />
                    <br />
                    <asp:Label ID="movie_rlsyear" runat="server" Font-Names="Arial" Font-Size="10pt"></asp:Label><br />
                    <br />
                    &nbsp;
                    <asp:DataList ID="movie_production" runat="server" CellPadding="4" ForeColor="#333333" Font-Bold="True" OnEditCommand="Edit_PC_Command" OnDeleteCommand="Delete_PC_Command">
                        <FooterStyle BackColor="PaleTurquoise" Font-Bold="True" ForeColor="White" HorizontalAlign="Right" />
                        <SelectedItemStyle BackColor="#C5BBAF" Font-Bold="True" ForeColor="#333333" />
                        <AlternatingItemStyle BackColor="White" />
                        <ItemStyle BackColor="#E3EAEB" />
                        <HeaderStyle BackColor="#1C5E55" Font-Bold="True" ForeColor="White" Width="500px" />
                        <ItemTemplate>
                           <table border=0>
                           <tr>
                           <td style="width: 500px"><%# DataBinder.Eval(Container.DataItem, "name") %>
                           </td></tr>
                           </table>
                        </ItemTemplate>
                        <HeaderTemplate>
                    Production Company
                        </HeaderTemplate>
                        <FooterTemplate>
                        <asp:LinkButton Text="Add" CommandName="Edit" Runat="server" ID="add" /> | <asp:LinkButton Text="Remove" CommandName="Delete" Runat="server" ID="remove" />
                        </FooterTemplate>
                    </asp:DataList></span><br />
                <asp:DataList ID="movie_studio" runat="server" CellPadding="4" ForeColor="#333333" Font-Bold="True" OnEditCommand="Edit_STUD_Command" OnDeleteCommand="Delete_STUD_Command">
                    <FooterStyle BackColor="PaleTurquoise" Font-Bold="True" ForeColor="White" Font-Size="10pt" HorizontalAlign="Right" />
                    <SelectedItemStyle BackColor="#C5BBAF" Font-Bold="True" ForeColor="#333333" /><ItemTemplate>
                        <table border=0>
                            <tr>
                                <td style="width: 500px">
                                    <%# DataBinder.Eval(Container.DataItem, "name") %>
                                </td>
                            </tr>
                        </table>
                    </ItemTemplate>
                    <AlternatingItemStyle BackColor="White" />
                    <ItemStyle BackColor="#E3EAEB" Font-Size="10pt" />
                    <HeaderTemplate>
                        Studios
                    </HeaderTemplate>
                    <FooterTemplate>
                            <asp:LinkButton Text="Add" CommandName="Edit" Runat="server" ID="add" /> | <asp:LinkButton Text="Remove" CommandName="Delete" Runat="server" ID="remove" />
                    </FooterTemplate>
                    <HeaderStyle BackColor="#1C5E55" Font-Bold="True" ForeColor="White" Font-Size="10pt" Width="500px" />
                </asp:DataList><br />
                <asp:DataList ID="movie_director" runat="server" CellPadding="4" ForeColor="#333333" Font-Bold="False" OnEditCommand="Edit_DIRS_Command" OnDeleteCommand="Delete_DIRS_Command">
                    <FooterStyle BackColor="PaleTurquoise" Font-Bold="True" ForeColor="White" Font-Size="10pt" HorizontalAlign="Right" />
                    <SelectedItemStyle BackColor="#C5BBAF" Font-Bold="True" ForeColor="#333333" />
                    <ItemTemplate>
                        <table border=0>
                            <tr>
                                <td style="width: 300px"><b>
                                    <%# DataBinder.Eval(Container.DataItem, "firstname") %> <%# DataBinder.Eval(Container.DataItem, "lastname") %>
                                </b></td>
                                <td style="width: 200px">
                                    <%# DataBinder.Eval(Container.DataItem, "detail_role") %>
                                </td>
                            </tr>
                        </table>
                    </ItemTemplate>
                    <AlternatingItemStyle BackColor="White" />
                    <ItemStyle BackColor="#E3EAEB" Font-Size="10pt" />
                    <HeaderTemplate>
                        Directors
                    </HeaderTemplate>
                    <FooterTemplate>
                            <asp:LinkButton Text="Add" CommandName="Edit" Runat="server" ID="add" /> | <asp:LinkButton Text="Remove" CommandName="Delete" Runat="server" ID="remove" />
                    </FooterTemplate>
                    <HeaderStyle BackColor="#1C5E55" Font-Bold="True" ForeColor="White" Font-Size="10pt" Width="500px" />
                </asp:DataList><br />
                <asp:DataList ID="movie_writers" runat="server" CellPadding="4" ForeColor="#333333" Font-Bold="False" OnEditCommand="Edit_WR_Command" OnDeleteCommand="Delete_WR_Command">
                    <FooterStyle BackColor="PaleTurquoise" Font-Bold="True" ForeColor="White" Font-Size="10pt" HorizontalAlign="Right" />
                    <SelectedItemStyle BackColor="#C5BBAF" Font-Bold="True" ForeColor="#333333" />
                    <ItemTemplate>
                        <table border=0>
                            <tr>
                                <td style="width: 300px"><b>
                                    <%# DataBinder.Eval(Container.DataItem, "firstname") %> <%# DataBinder.Eval(Container.DataItem, "lastname") %>
                                </b></td>
                                <td style="width: 200px">
                                    <%# DataBinder.Eval(Container.DataItem, "detail_role") %>
                                </td>
                            </tr>
                        </table>
                    </ItemTemplate>
                    <AlternatingItemStyle BackColor="White" />
                    <ItemStyle BackColor="#E3EAEB" Font-Size="10pt" />
                    <HeaderTemplate>
                        Writers
                    </HeaderTemplate>
                    <FooterTemplate>
                            <asp:LinkButton Text="Add" CommandName="Edit" Runat="server" ID="add" /> | <asp:LinkButton Text="Remove" CommandName="Delete" Runat="server" ID="remove" />
                    </FooterTemplate>
                    <HeaderStyle BackColor="#1C5E55" Font-Bold="True" ForeColor="White" Font-Size="10pt" Width="500px" />
                </asp:DataList><br />
                <asp:DataList ID="movie_producers" runat="server" CellPadding="4" ForeColor="#333333" Font-Bold="False" OnEditCommand="Edit_PROD_Command" OnDeleteCommand="Delete_PROD_Command">
                    <FooterStyle BackColor="PaleTurquoise" Font-Bold="True" ForeColor="White" Font-Size="10pt" HorizontalAlign="Right"/>
                    <SelectedItemStyle BackColor="#C5BBAF" Font-Bold="True" ForeColor="#333333" />
                    <ItemTemplate>
                        <table border="0" >
                            <tr>
                                <td style="width: 300px"><b>
                                    <%# DataBinder.Eval(Container.DataItem, "firstname") %> <%# DataBinder.Eval(Container.DataItem, "lastname") %>
                                </b></td>
                                <td style="width: 200px">
                                    <%# DataBinder.Eval(Container.DataItem, "detail_role") %>
                                </td>
                            </tr>
                        </table>
                    </ItemTemplate>
                    <AlternatingItemStyle BackColor="White" />
                    <ItemStyle BackColor="#E3EAEB" Font-Size="10pt" />
                    <HeaderTemplate >
                        Producers
                    </HeaderTemplate>
                    <FooterTemplate>
                            <asp:LinkButton Text="Add" CommandName="Edit" Runat="server" ID="add" /> | <asp:LinkButton Text="Remove" CommandName="Delete" Runat="server" ID="remove" />
                    </FooterTemplate>
                    <HeaderStyle BackColor="#1C5E55" Font-Bold="True" Font-Size="10pt" ForeColor="White" Width="500px" />
                </asp:DataList><br />
                <asp:DataList ID="movie_actors" runat="server" CellPadding="4" ForeColor="#333333" Font-Bold="False" OnEditCommand="Edit_ACT_Command" OnDeleteCommand="Delete_ACT_Command">
                    <FooterStyle BackColor="PaleTurquoise" Font-Bold="True" ForeColor="White" Font-Size="10pt" HorizontalAlign="Right" />
                    <SelectedItemStyle BackColor="#C5BBAF" Font-Bold="True" ForeColor="#333333" />
                    <ItemTemplate>
                        <table border="0" >
                            <tr>
                                <td style="width: 300px"><b>
                                    <%# DataBinder.Eval(Container.DataItem, "firstname") %> <%# DataBinder.Eval(Container.DataItem, "lastname") %>
                                </b></td>
                                <td style="width: 200px">
                                    <%# DataBinder.Eval(Container.DataItem, "detail_role") %>
                                </td>
                            </tr>
                        </table>
                    </ItemTemplate>
                    <AlternatingItemStyle BackColor="White" />
                    <ItemStyle BackColor="#E3EAEB" Font-Size="10pt" />
                    <HeaderTemplate >
                        Actors
                    </HeaderTemplate>
                    <FooterTemplate>
                            <asp:LinkButton Text="Add" CommandName="Edit" Runat="server" ID="add" /> | <asp:LinkButton Text="Remove" CommandName="Delete" Runat="server" ID="remove" />
                    </FooterTemplate>
                    <HeaderStyle BackColor="#1C5E55" Font-Bold="True" Font-Size="10pt" ForeColor="White" Width="500px" />
                </asp:DataList><br />
                <asp:DataList ID="movie_genre" runat="server" CellPadding="4" ForeColor="#333333" Font-Bold="False" OnEditCommand="Edit_GEN_Command" OnDeleteCommand="Delete_GEN_Command">
                    <FooterStyle BackColor="PaleTurquoise" Font-Bold="True" ForeColor="White" Font-Size="10pt" HorizontalAlign="Right" />
                    <SelectedItemStyle BackColor="#C5BBAF" Font-Bold="True" ForeColor="#333333" />
                    <ItemTemplate>
                        <table border="0" >
                            <tr>
                                <td style="width: 500px">
                                    <%# DataBinder.Eval(Container.DataItem, "name") %>
                                </td>
                            </tr>
                        </table>
                    </ItemTemplate>
                    <AlternatingItemStyle BackColor="White" />
                    <ItemStyle BackColor="#E3EAEB" Font-Size="10pt" />
                    <HeaderTemplate >
                        Genre
                    </HeaderTemplate>
                    <FooterTemplate>
                            <asp:LinkButton Text="Add" CommandName="Edit" Runat="server" ID="add" /> | <asp:LinkButton Text="Remove" CommandName="Delete" Runat="server" ID="remove" />
                    </FooterTemplate>
                    <HeaderStyle BackColor="#1C5E55" Font-Bold="True" Font-Size="10pt" ForeColor="White" Width="500px" />
                </asp:DataList>&nbsp;</div>
            <br />
            <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:moviedbConnectionString %>"
                SelectCommand="SELECT [movieid], [title] FROM [movie] ORDER BY [title]"></asp:SqlDataSource>
            <strong>
            <br />
            </strong></span>
    
    </div>
    </form>
</body>
</html>

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// Common functions used for iceman
/// </summary>
namespace IceMan
{
    public class Database
    {
        public static string GetConnectionString( string strCSName )
        {
            System.Configuration.Configuration webDOTconfig;
            String strConnection;

            webDOTconfig = System.Web.Configuration.WebConfigurationManager.OpenWebConfiguration("/iceman");
            if (webDOTconfig.ConnectionStrings.ConnectionStrings.Count > 0)
            {
                strConnection = webDOTconfig.ConnectionStrings.ConnectionStrings[strCSName].ConnectionString.ToString();
            }
            else
            {
                throw new ApplicationException("Could not load the connection string");
            }

            return strConnection;
        }
    }
}
// -*- mode: c++ -*-
// Copyright 2010, François Bleibel, Thomas Moulard, Olivier Stasse,
// JRL, CNRS/AIST.
//
// This file is part of dynamic-graph.
// dynamic-graph is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// dynamic-graph is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// dynamic-graph. If not, see <http://www.gnu.org/licenses/>.

#ifndef DYNAMIC_GRAPH_PLUGIN_LOADER_H
# define DYNAMIC_GRAPH_PLUGIN_LOADER_H
# include <list>
# include <string>
# include <map>

# include <dynamic-graph/fwd.hh>
# include <dynamic-graph/dynamic-graph-api.h>

namespace dynamicgraph
{
  /*! @ingroup dgraph

    \brief Loads plugins from dynamic libraries (usually .so or .dll
    files).

    The sotPluginLoader can be made to load individual plugins by
    specifying their filenames to addPlugin () or reading them from a
    configuration file (loadPluginlist).  Once loaded, the plugins
    register themselves to the sotFactory and the related objects can
    subsequently be instantiated by the sotInterpretor for example.

  */
  class DYNAMIC_GRAPH_DLLAPI PluginLoader
  {
  public:
    /*! \brief Default constructor. */
    PluginLoader ();
    ~PluginLoader ();

    /*! \brief Set the directory from which to load the dynamic libraries
      containing the plugins. */
    const std::string& setDirectory (const std::string& n);
    /*! \brief Get the directory from which to load the dynamic libraries
      containing the plugins. */
    const std::string& getDirectory () const;

    /*! \brief Adds a list of plugins

      It is done by reading the file configFile which contains for
      each line a plugin name.

      \par[in] configFile: The name of the file which contains the
      plugins name.
      \par[in] dir: The name of the directory which contains the
      dynamic libraries.
    */
    void loadPluginList (const std::string& configFile,
			 const std::string& dir = "");

    /*! \brief Adds a single plugin */
    void addPlugin (const std::string& name,
		    const std::string& dir = "");

    /*! \brief Load the plugins previously added */
    void loadPlugins ();

    /*! \brief Remove from the user memory the dynamic library related
        to the plugin. */
    void unloadPlugin (const std::string& plugname);

    /*! \brief Remove all the dynamic libraries related to the plugins.
      For non-re-entrant plugins this method HAS TO be called. */
    void unloadAllPlugins ();

    const std::map<std::string, std::string>& getLoadedPluginNames () const
    {
      return loadedPluginNames;
    }

    const std::string& searchPlugin (const std::string& plugname);

  protected:
    /*! \brief Directory from where the dynamic libraries are loaded. */
    std::string pluginDirectory;

    /*! \brief List of plugin names given by their name postfixed to
        the directory. */
    std::list< std::string > pluginNames;

    /*! \brief If a plugin has been loaded then this map contains
      the name of the plugin.
      \note This field looks useless.
    */
    std::map<std::string, std::string> loadedPluginNames;

    /*! \brief Keeps a reference to the library according to the name of the
      plugin. */
    PluginRefMap* pluginRefs;
  };

} // end of namespace dynamicgraph.

#endif //! DYNAMIC_GRAPH_PLUGIN_LOADER_H

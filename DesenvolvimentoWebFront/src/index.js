import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import ReactDOM from 'react-dom/client';
import './index.css';
//import App from './App';
import App from './App.js'
import reportWebVitals from './reportWebVitals';

import {createBrowserRouter, Navigate, RouterProvider} from 'react-router-dom';
import ErrorScreen from './screens/ErrorScreen.js';

import Home from './screens/Home2.js';
import Contact from './screens/Contact.js';

import CadastrarScreen from './screens/CadastrarScreen.js';
import Login from './screens/Login.js';
import Logout from './screens/Logout.js';
import AddEvento from './screens/AddEvento.js';
import DeleteEvento from './screens/DeleteEvento.js';
import UpdateEvento from './screens/UpdateEvento.js';
import GetEventoId from './screens/GetEventoId.js';
import GetEventoAll from './screens/GetEventoAll.js';
import AddIngresso from './screens/AddIngresso.js';
import AddLocal from './screens/AddLocal.js';
import AddCompra from './screens/AddCompra.js';

const router = createBrowserRouter([
    {
        path: "/",
        element: <App />,
        errorElement: <ErrorScreen/>,
        children: [
            {
                path: "/",
                element: <Home />
              },
              {
                path: "contact",
                element: <Contact />
              },            
              {
                path: "addevento",
                element: <AddEvento />
              },
              {
                path: "deleteevento",
                element: <DeleteEvento />
              },
              {
                path: "updateevento",
                element: <UpdateEvento />
              },    
              {
                path: "geteventoId",
                element: <GetEventoId />
              },    
              {
                path: "geteventoAll",
                element: <GetEventoAll />
              },    
              {
                path: "addingresso",
                element: <AddIngresso />
              },
              {
                path: "addlocal",
                element: <AddLocal />
              },
              {
                path: "addcompra",
                element: <AddCompra />
              },
              {
                path: "/login",
                element: <Login />
              },              
              {
                  path: "/cadastrar",
                  element: <CadastrarScreen />
              },               
              {
                  path: "/logout",
                  element: <Logout />
              },                              
              {
                path:"oldpage",
                element: <Navigate to="/" />
              }

        ]
    }
]);

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
    <RouterProvider router={router}/>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();

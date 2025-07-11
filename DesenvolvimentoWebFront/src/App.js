import './App.css';
import './styles/ExemploCss.css'
import { Link } from 'react-router-dom';
import { Navbar, Nav } from "react-bootstrap";

import { Outlet } from 'react-router-dom';

function App() {
  return (
    <div className="App">
    <Navbar bg="dark" variant="dark" expand="lg">
      <Navbar.Brand href="/">
        {/* <img src="/home/web/desenvolvimento-web-front/fundo.jpg" width="30" height="30" class="d-inline-block align-top" alt=""/> */}
        UniVento</Navbar.Brand>
      <Navbar.Toggle aria-controls="basic-navbar-nav" />
      <Navbar.Collapse id="basic-navbar-nav">
        <Nav className="mr-auto">
          <Nav.Link as={Link} to="/">Home</Nav.Link>
          <Nav.Link as={Link} to="/login">Sign in</Nav.Link>
          <Nav.Link as={Link} to="/cadastrar">Sign up</Nav.Link>
          <Nav.Link as={Link} to="/logout">Logout</Nav.Link>
          <Nav.Link as={Link} to="/addevento">Add Evento</Nav.Link>
          <Nav.Link as={Link} to="/deleteevento">Delete Evento</Nav.Link>
          <Nav.Link as={Link} to="/updateevento">Atualizar Evento</Nav.Link>
          <Nav.Link as={Link} to="/addingresso">Add Ingresso</Nav.Link>
          <Nav.Link as={Link} to="/addlocal">Add Local</Nav.Link>
          <Nav.Link as={Link} to="/addcompra">Add Compra</Nav.Link>
          <Nav.Link as={Link} to="/geteventoid">Ver Evento</Nav.Link>
          <Nav.Link as={Link} to="/geteventoall">Todos Eventos</Nav.Link>
        </Nav>
      </Navbar.Collapse>
    </Navbar>
    <Outlet/>
    </div>
  );
}

export default App;

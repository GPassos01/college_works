import React from "react";
import { useNavigate } from "react-router-dom";

function Logout() {

    const Make_logout = () => {
        localStorage.clear();
        return "Deslogado"
    }


  return (
        <div><Make_logout /></div>
  );
}

export default Logout;
import React, { useState } from "react";
import axios from "axios";

export default function LoginScreen() {
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [errorMessage, setErrorMessage] = useState("");

  const handleSubmit = async (e) => {
    e.preventDefault();


    const request_body = {
      "login": email,
      "password": password
    }
    try {
      const response = await axios.post("http://localhost:8080/auth/login", request_body);
      const { token } = response.data;
      localStorage.setItem("token", token);
      console.log("Login successful! Token saved in local storage:", token);
      // Optionally, you can redirect the user to another page or perform other actions upon successful login
    } catch (error) {
      console.error("Error logging in:", error);
      setErrorMessage("Invalid email or password");
      // Handle error appropriately, e.g., display an error message to the user
    }
  };

  return (
    <div>
      <h1>Login</h1>
      {errorMessage && <p>{errorMessage}</p>}
      <form onSubmit={handleSubmit}>
        <div>
          <label htmlFor="email">Email:</label>
          <input
            type="email"
            id="email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            required
          />
        </div>
        <div>
          <label htmlFor="password">Password:</label>
          <input
            type="password"
            id="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            required
          />
        </div>
        <button type="submit">Login</button>
      </form>
    </div>
  );
}